#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
{

}


void MessageHandler::Start()
{
     /*while (WorkerAgent::Empty()) {}
     std::this_thread::sleep_for(std::chrono::seconds(10));
     Peers first = WorkerAgent::First();
     WorkerAgent::SendMessage(first.GetHost(),first.GetPort(),"Testmessage");

     QHostAddress host;
     int port;

     char * data = new char[100];
     while(!WorkerAgent::IsWaitingMessage())
     {

     }

    WorkerAgent::GetFirstMessage(host, port, data);
    Traces() << "\n" << "LOG: New data from worker: " << QString(data);

    delete [] data;*/

    char * data = new char[4048];
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
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error!";
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
        } else
        if (state == Peers::STATE::FREE)
        {
            WorkerAgent::SetState(ho, po, Peers::STATE::FREE);
        } else
        {
            Traces() << "\n" << "ERR: Wrong peer state!";
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error!";
    }
}
