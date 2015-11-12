#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
               : boardQueue(nullptr),
                 shareJobs(false),
                 endFlag(false),
                 active(true)
{

}

void MessageHandler::SetBoardQueue(ThreadIABoardQueue<900000> *wsk)
{
    boardQueue = wsk;
}

void MessageHandler::Start()
{
    char * data = new char[ProgramVariables::K4];
    QHostAddress host;
    int port;

    while(!endFlag)
    {
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
            //TEMPORATY SLEEP Traces() << "\n" << "LOG: Tryning share jobs";

            if (WorkerAgent::GetFreeStateNumber() > 0)
            {                
                if (ProgramVariables::GetSecondsSinceEpoch() - startTime > ProgramVariables::GetMaxSecondsToEnd())
                {
                    if (boardQueue->Size() > 0)
                    {
                        QHostAddress ho;
                        int po;
                        WorkerAgent::GetFirstFreePeers(ho, po);

                        Traces() << "\n" << "LOG: Take first board";
                        Board board = boardQueue->First();

                        if (!board.GetNullBoard())
                        {
                            char *data = new char[ProgramVariables::K4];

                            MessageCoder::ClearChar(data, ProgramVariables::K4);
                            std::string tempId = ProgramVariables::CreateMessageId();
                            std::string jobId = ProgramVariables::CreateMessageId();
                            MessageCoder::CreateStartMessage(10, 1, tempId, jobId, data);
                            MessageCoder::BoardToChar(board, data, 1);
                            WorkerAgent::SendMessage(ho, po, data);
                            WorkerAgent::SetState(ho, po, Peers::STATE::BUSY);
                            CreateOkGuard(ho, po, tempId, jobId, WorkersState::START_WORK_OK);
                            jobList.push_back(jobId);
                        }

                    }
                }
            }
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

    }


    active = false;
    delete [] data;
}

void MessageHandler::MessageInterpreting(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: MessageHandler::MessageInterpreting(const std::map<std::string, std::string> data)";

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
            CreateOkGuard(ho, po, "", "", WorkersState::NONE_OK);
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


void MessageHandler::TakeSetState(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: MessageHandler::TakeSetState(const std::map<std::string, std::string> data)";

    try
    {
        int state;
        state = std::atoi(data.at(MessageCoder::STATE).c_str());

        if (state == Peers::STATE::BUSY)
        {
            WorkerAgent::SetState(ho, po, Peers::STATE::BUSY);            
            char *dest = new char[ProgramVariables::K4];
            MessageCoder::ClearChar(dest, ProgramVariables::K4);
            MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
            WorkerAgent::SendMessage(ho, po, dest);            
        } else
        if (state == Peers::STATE::FREE)
        {
            WorkerAgent::SetState(ho, po, Peers::STATE::FREE);            
            char *dest = new char[ProgramVariables::K4];
            MessageCoder::ClearChar(dest, ProgramVariables::K4);
            MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
            WorkerAgent::SendMessage(ho, po, dest);            
        } else
        {
            Traces() << "\n" << "ERR: Wrong peer state! host:" << ho.toString() << ":" << po;
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}

void MessageHandler::TakeBestResult(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: MessageHandler::TakeBestResult(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)";

    try
    {
        if (std::find(jobList.begin(), jobList.end(), data.at(MessageCoder::JOB_ID)) == jobList.end())
        {
            Traces() << "\n" << "ERR: TakeBestResult: Job not founded!";
        } else
        {
            jobList.remove(data.at(MessageCoder::MESSAGE_ID));
            Board temp;
            MessageCoder::MapToBoard(data, &temp);
            qDebug() << "Num of elements before workers" << boardQueue->Size();
            boardQueue->PushBack(temp);
            qDebug() << "Num of elements after workers" << boardQueue->Size();

            WorkerAgent::SetState(ho, po, Peers::STATE::FREE);
            char *dest = new char[ProgramVariables::K4];
            MessageCoder::ClearChar(dest, ProgramVariables::K4);
            MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
            WorkerAgent::SendMessage(ho, po, dest);
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}

void MessageHandler::CreateOkGuard(const QHostAddress ho, const int po, std::string id, std::string jobId, WorkersState::MessageState state)
{
    std::string key = ho.toString().toStdString() + std::to_string(po);

    try
    {
        WorkersState *wsk = workersState.at(key);
        wsk->SetPeer(ho, po);
        wsk->SetOKExpected(id, jobId, state);
    }
    catch (std::out_of_range)
    {
        WorkersState *wsk = new WorkersState();
        wsk->SetPeer(ho, po);
        wsk->SetOKExpected(id, jobId, state);
        workersState[key] = wsk;
        workersStateList.push_back(key);
    }
}

void MessageHandler::NoResponseFromWorker(WorkersState *wsk)
{
    if (wsk->GetState() == WorkersState::START_WORK_OK)
    {
        WorkerAgent::SetState(wsk->GetHost(), wsk->GetPort(), Peers::STATE::FREE);
        wsk->SetNone();
        jobList.remove(wsk->GetJobId());
    }
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
