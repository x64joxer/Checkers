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

void Peers::AddData(char *dat)
{
    if (strlen(dat)>0)
    {
        char *temp = new char[strlen(dat)+1];
        data.push_back(temp);
    };
}

void Peers::GetData(char *dat)
{
    if (!data.empty())
    {
        char *temp = data.front();
        data.pop_front();
        dat = new char[strlen(temp)+1];
        strcpy(dat,temp);
        delete [] temp;
    } else
    {
        Traces() << "\n" << "ERROR: No data!";
    };
}

bool Peers::operator==(const Peers &data)
{
    if ((host == data.host)&&(port==data.port)) return true;
    return false;
}