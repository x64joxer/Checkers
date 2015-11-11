#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
               : boardQueue(nullptr),
                 shareJobs(false)
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

    while(true)
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
                            MessageCoder::CreateStartMessage(10, 1, tempId, data);
                            MessageCoder::BoardToChar(board, data, 1);
                            WorkerAgent::SendMessage(ho, po, data);
                            WorkerAgent::SetState(ho, po, Peers::STATE::BUSY);                                                                                    
                        }

                    }
                }
            }
        }
    }

    delete [] data;
}

void MessageHandler::MessageInterpreting(const QHostAddress ho, const int po, const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: MessageHandler::MessageInterpreting(const std::map<std::string, std::string> data)";

    try
    {
        std::string action = data.at(MessageCoder::ACTION);

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
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error host:" << ho.toString() << ":" << po;
    }
}

void MessageHandler::CreateOkGuard(const QHostAddress ho, const int po, std::string id, WorkersState::MessageState state)
{
    try
    {
        std::string key = ho.toString().toStdString() + std::to_string(po);
        workersState.at(key);
        Traces() << "\n" << "ERR: Server alreay waiting for worker";
    }
    catch (std::out_of_range)
    {
        WorkersState *wsk = new WorkersState();
        wsk->SetPeer(ho, po);
        wsk->SetOKExpected(id, state);
    }
}
