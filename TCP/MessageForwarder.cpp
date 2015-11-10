#include "TCP/MessageForwarder.h"

MessageForwarder::MessageForwarder(QObject *parent) : QObject(parent)
{

}

void MessageForwarder::SendMessage(const QHostAddress ho, const int po, char* data)
{    
    emit Send(ho,po,data);
}

