#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
               : boardQueue(nullptr),
                 shareJobs(false),
                 endFlag(false),
                 active(true)
{

}

void MessageHandler::SetBoardQueue(ThreadIABoardQueue<3000000> *wsk)
{
    boardQueue = wsk;
}

void MessageHandler::Start()
{
    char * data = new char[ProgramVariables::K4];
    QHostAddress host;
    int port;
    std::mutex mutex_guard;    

    while(!endFlag)                
    {

        {

            std::unique_lock<std::mutex> guard(mutex_guard);
            ProgramVariables::GetGlobalConditionVariableNetwork()->wait(guard,[this]
            {
                return WorkerAgent::IsWaitingMessage() |
                       ((WorkerAgent::GetFreeStateNumber() > 0) & shareJobs & (!ProgramVariables::IsMaxWorkersReached())) |
                       (WorkersState::GetGlobNumOfWaitingTimer()>0) |
                       endFlag |
                       (WorkerAgent::GetNumberOfPeers() < workersStateList.size()); }
            );
            mutex_guard.unlock();
        }

        if (WorkerAgent::IsWaitingMessage())
        {
            std::map<std::string, std::string> recMessage;

            WorkerAgent::GetFirstMessage(host, port, data);
            MessageCoder::MessageToMap(data, recMessage);
            MessageInterpreting(host, port, recMessage);
        }

        //Share jobs
        if (shareJobs)
        {
            if ((WorkerAgent::GetFreeStateNumber() > 0) && (!ProgramVariables::IsMaxWorkersReached()))
            {                
                if (TakeSecondsToEnd() > ProgramVariables::GetMaxSecondsToEnd())
                {
                    TRACE01 Traces() << "\n" << "LOG: Time to end " << ProgramVariables::GetMaxTimeForIa() - (ProgramVariables::GetSecondsSinceEpoch() - startTime);

                    if (boardQueue->Size() > 0)
                    {
                        QHostAddress ho;
                        int po;
                        WorkerAgent::GetFirstFreePeers(ho, po);

                        TRACE01 Traces() << "\n" << "LOG: Take first board";
                        Board board = boardQueue->First(1);

                        if (!board.GetNullBoard())
                        {
                            char *data = new char[ProgramVariables::K4];

                            MessageCoder::ClearChar(data, ProgramVariables::K4);
                            std::string tempId = ProgramVariables::CreateMessageId();
                            std::string jobId = ProgramVariables::CreateMessageId();
                            MessageCoder::CreateStartMessage(TakeSecondsToEnd(), 1, tempId, jobId, data);
                            MessageCoder::BoardToChar(board, data, 1);
                            WorkerAgent::SendMessage(ho, po, data);
                            WorkerAgent::SetState(ho, po, Peers::STATE::BUSY);
                            ProgramVariables::IncreaseUsedWorkers();
                            CreateOkGuard(ho, po, tempId, jobId, WorkersState::START_WORK_OK);                            
                            jobList.push_back(jobId);
                        }

                    }
                }
            }
        } else
        {
            ClerWorkerStateOfUnconnected();
        }
        //Share jobs end

        //Check timeout for OK messages
        std::for_each(workersStateList.begin(), workersStateList.end(),
        [this] (std::string &n)
        {
            if (workersState.at(n)->GetTimeout())
            {
                NoResponseFromWorker(workersState.at(n));
            }
        });

        //Clear all unnecessary state objects
        if (WorkerAgent::GetNumberOfPeers() < workersStateList.size())
        {
            ClerWorkerStateOfUnconnectedNoneOkWorkers();
        }

    }


    active = false;
    delete [] data;
}

unsigned long long MessageHandler::TakeSecondsToEnd()
{
    unsigned long long howManyPass = (ProgramVariables::GetSecondsSinceEpoch() - startTime);

    if (ProgramVariables::GetMaxTimeForIa() > howManyPass)
    {
       return ProgramVariables::GetMaxTimeForIa() - howManyPass;
    } else
    {
       return 0;
    }
}

void MessageHandler::MessageInterpreting(const QHostAddress ho, const int po, const std::map<std::string, std::string> & data)
{
    TRACE01 Traces() << "\n" << "LOG: MessageHandler::MessageInterpreting(const std::map<std::string, std::string> data)";

    try
    {
        std::string action = data.at(MessageCoder::ACTION);
        WorkersState *current;

        try
        {
            current = workersState.at(ho.toString().toStdString() + std::to_string(po));
        }
        catch (std::out_of_range)
        {
            current = CreateOkGuard(ho, po, "", "", WorkersState::NONE_OK);
        }

        if ((action != MessageCoder::OK)&&(current->GetState() != WorkersState::NONE_OK))
        {
            Traces() << "\n" << "ERR: Expected OK message from worker!";
        } else
        if (action == MessageCoder::SET_STATE)
        {
            TakeSetState(ho, po, data);
        } else
        if (action == MessageCoder::BEST_RESULT)
        {
            TakeBestResult(ho, po, data);
        } else
        if (action == MessageCoder::OK)
        {
            if (current->GetState() == WorkersState::NONE_OK)
            {
                Traces() << "\n" << "ERR: Unexpected OK message from server!";
            } else
            if (data.at(MessageCoder::MESSAGE_ID) != current->GetID())
            {
                Traces() << "\n" << "ERR: Unexpected OK message ID from server!";
            } else
            {
                current->SetNone();
            }
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}


void MessageHandler::TakeSetState(const QHostAddress ho, const int po, const std::map<std::string, std::string> & data)
{
    TRACE01 Traces() << "\n" << "LOG: MessageHandler::TakeSetState(const std::map<std::string, std::string> data)";

    try
    {
        int state;
        state = std::atoi(data.at(MessageCoder::STATE).c_str());

        if (state == Peers::STATE::BUSY)
        {
            WorkerAgent::SetState(ho, po, Peers::STATE::BUSY);               
        } else
        if (state == Peers::STATE::FREE)
        {
            WorkerAgent::SetState(ho, po, Peers::STATE::FREE);            
        } else
        {
            Traces() << "\n" << "ERR: Wrong peer state! host:" << ho.toString() << ":" << po;
            throw std::out_of_range("Wrong peer state");
        }

        WorkerAgent::SetNumberOfThread(ho, po, std::atoi(data.at(MessageCoder::NUM_OF_THREAD).c_str()));

        char *dest = new char[ProgramVariables::K4];
        MessageCoder::ClearChar(dest, ProgramVariables::K4);
        MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
        WorkerAgent::SendMessage(ho, po, dest);
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}

void MessageHandler::TakeBestResult(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)
{
    TRACE01 Traces() << "\n" << "LOG: MessageHandler::TakeBestResult(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)";

    try
    {
        if (std::find(jobList.begin(), jobList.end(), data.at(MessageCoder::JOB_ID)) == jobList.end())
        {
            Traces() << "\n" << "ERR: TakeBestResult: Job not founded!";
        } else        
        if (shareJobs)
        {
            jobList.remove(data.at(MessageCoder::MESSAGE_ID));
            Board temp;
            MessageCoder::MapToBoard(data, &temp);
            std::string tempNumOfanalysed = data.at(MessageCoder::NUM_OF_ANALYSED);
            ProgramVariables::IncreaseNumOfAnalyded(std::stoll(tempNumOfanalysed));
            Traces() << "\n" << "LOG: Number of branch analysed by worker " << ho.toString() << ":" << po << " = " << QString(tempNumOfanalysed.c_str());
            TRACE01 boardQueue->PushBack(temp);

            WorkerAgent::SetState(ho, po, Peers::STATE::FREE);
            char *dest = new char[ProgramVariables::K4];
            MessageCoder::ClearChar(dest, ProgramVariables::K4);
            ProgramVariables::DecreaseUsedWorkers();
            MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
            WorkerAgent::SendMessage(ho, po, dest);
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}

WorkersState * MessageHandler::CreateOkGuard(const QHostAddress ho, const int po, const std::string & id, const std::string & jobId, WorkersState::MessageState state)
{
    std::string key = ho.toString().toStdString() + std::to_string(po);
    WorkersState *wsk;

    try
    {
        wsk = workersState.at(key);
        wsk->SetPeer(ho, po);
        wsk->SetOKExpected(id, jobId, state);        
    }
    catch (std::out_of_range)
    {
        wsk = new WorkersState();
        wsk->SetPeer(ho, po);
        wsk->SetOKExpected(id, jobId, state);
        workersState[key] = wsk;
        workersStateList.push_back(key);
    }

    return wsk;
}

void MessageHandler::NoResponseFromWorker(WorkersState *wsk)
{
    if (wsk->GetState() == WorkersState::START_WORK_OK)
    {
        Traces() << "\n" << "ERR: No response from worker!";

        WorkerAgent::SetState(wsk->GetHost(), wsk->GetPort(), Peers::STATE::FREE);
        ProgramVariables::DecreaseUsedWorkers();
        wsk->SetNone();
        jobList.remove(wsk->GetJobId());
    }
}

void MessageHandler::ClerWorkerStateOfUnconnected()
{
    WorkersState *wsk;
    std::list<std::string> workersStateListToRemove;

    std::for_each(workersStateList.begin(), workersStateList.end(),
    [this, &wsk, &workersStateListToRemove] (std::string &n)
    {
        wsk = workersState.at(n);

        if (!WorkerAgent::Exist(wsk->GetHost(), wsk->GetPort()))
        {
            delete workersState.at(n);
            workersStateListToRemove.push_back(n);
        }
    });

    std::for_each(workersStateListToRemove.begin(), workersStateListToRemove.end(),
    [this] (std::string &n)
    {
       workersState.erase(n);
       workersStateList.remove(n);
    });
}

void MessageHandler::ClerWorkerStateOfUnconnectedNoneOkWorkers()
{
    WorkersState *wsk;
    std::list<std::string> workersStateListToRemove;

    std::for_each(workersStateList.begin(), workersStateList.end(),
    [this, &wsk, &workersStateListToRemove] (std::string &n)
    {
        wsk = workersState.at(n);

        if (wsk->GetState() == WorkersState::NONE_OK)
        {
            if (!WorkerAgent::Exist(wsk->GetHost(), wsk->GetPort()))
            {
                delete workersState.at(n);
                workersStateListToRemove.push_back(n);
            }
        }
    });

    std::for_each(workersStateListToRemove.begin(), workersStateListToRemove.end(),
    [this] (std::string &n)
    {
       workersState.erase(n);
       workersStateList.remove(n);
    });
}

void MessageHandler::ClearWorkersStateList()
{
    std::for_each(workersStateList.begin(), workersStateList.end(),
    [this] (std::string &n)
    {
        delete workersState.at(n);
    });
}

MessageHandler::~MessageHandler()
{
    ClearWorkersStateList();
}
