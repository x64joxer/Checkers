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
            emit Send(temp.GetHost(), temp.GetPort(), "Wiadomosc");

            break;
        };
    };
}

