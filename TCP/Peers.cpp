#include "TCP/Peers.h"

Peers::Peers()
      : state(NONE),
        isNull(false),
        numOfThread(0)
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
        strcpy(temp,dat);
        data.push_back(temp);        
    };
}

void Peers::GetData(char *dat)
{
    if (!data.empty())
    {
        char *temp = data.front();
        data.pop_front();
        strcpy(dat,temp);        
        delete [] temp;
    } else
    {
        Traces() << "\n" << "ERROR: No data!";
    };
}

Peers::STATE Peers::GetState() const
{
    return state;
}

void Peers::SetState(const STATE val)
{
    state = val;
}

bool Peers::operator==(const Peers &data)
{
    if ((host == data.host)&&(port==data.port)) return true;
    return false;
}

Peers::~Peers()
{
    std::for_each(data.begin(),data.end(),  [](char *val) { delete val; });
}
