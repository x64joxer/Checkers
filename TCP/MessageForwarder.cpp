#include "TCP/MessageForwarder.h"

MessageForwarder::MessageForwarder(QObject *parent) : QObject(parent)
{

}

void MessageForwarder::Start()
{
    while(true)
    {
        if (!peers->Empty())
        {
            Peers temp = peers->First();
            server->SendMessage(temp.GetHost(), temp.GetPort(), "Wiadomosc");
            break;
        };
    };
}

