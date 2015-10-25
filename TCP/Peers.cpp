#include "TCP/Peers.h"

Peers::Peers()
{

}

void Peers::SetPeer(QHostAddress ho, int po)
{
    host = ho;
    port = po;
}

QHostAddress Peers::GetHost()
{
    return host;
}

int Peers::GetPort()
{
   return port;
}

bool Peers::operator==(const Peers &data)
{
    if ((host == data.host)&&(port==data.port)) return true;
    return false;
}
