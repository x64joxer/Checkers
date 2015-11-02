#ifndef PEERS_H
#define PEERS_H

#include <QHostAddress>
#include <list>
#include <iostream>
#include <string>
#include "Traces/Traces.h"

class Peers
{
    public:
        Peers();
        void SetPeer(QHostAddress ho, int po);
        QHostAddress GetHost();
        int GetPort();
        void AddData(char *dat);
        void GetData(char *dat);

        bool operator==(const Peers &);
    private:
        QHostAddress host;
        int port;
        std::list<char*> data;
};

#endif // PEERS_H
