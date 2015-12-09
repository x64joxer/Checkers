#include "TCP/TCPSocket.h"

TCPSocket::TCPSocket(QObject *parent) : QObject(parent),
             wsk(nullptr),
             dataToRemove(nullptr)
{
    qRegisterMetaType<QHostAddress >("QHostAddress");
}

void TCPSocket::NewDataFromClient()
{
    char * data;
    data  = new char[wsk->bytesAvailable()];
    wsk->read(data, wsk->bytesAvailable());
    TRACE01 Traces() << "\n" << "LOG: Data from worker " << wsk->peerAddress().toString() << ":" << wsk->peerPort() << ":" << QString(data);

    emit NewData(wsk->peerAddress(), wsk->peerPort(), data);

    delete [] data;
}

TCPSocket::~TCPSocket()
{
    wsk->deleteLater();
    delete [] dataToRemove;
}
