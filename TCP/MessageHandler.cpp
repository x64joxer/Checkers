#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
{

}


void MessageHandler::Start()
{
     while (WorkerAgent::Empty()) {}
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

    delete [] data;
    while(true) {}
}
