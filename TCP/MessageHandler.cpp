#include "TCP/MessageHandler.h"

MessageHandler::MessageHandler()
{

}


void MessageHandler::Start()
{
    while (peerQueue->Empty()) {}
    std::this_thread::sleep_for(std::chrono::seconds(10));
    Peers first = peerQueue->First();
    //peerQueue->SendMessage(first.GetHost(),first.GetPort(),"Testmessage");
    messageForwarder->SendMessage(first.GetHost(),first.GetPort(),"Testmessage");

    while(true) {}
}
