#include "TCP/TCPSocket.h"

TCPSocket::TCPSocket()
           : wsk(nullptr),
             dataToRemove(nullptr)
{

}

TCPSocket::~TCPSocket()
{
    wsk->deleteLater();
    delete [] dataToRemove;
}
