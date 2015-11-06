#include "TCP/MessageForwarder.h"

MessageForwarder::MessageForwarder(QObject *parent) : QObject(parent)
{

}

void MessageForwarder::Start()
{    
            Peers temp = peers->First();
            emit Send(temp.GetHost(), temp.GetPort(), "Wiadomosc");   
}

void MessageForwarder::SendMessage(const QHostAddress ho, const int po, char* data)
{    
    emit Send(ho,po,data);
}

