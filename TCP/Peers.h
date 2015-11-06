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
        bool IsData() { return !data.empty(); }

        enum  STATE { BUSY, FREE };

        STATE GetState() const;
        void SetState(const STATE val);

        bool operator==(const Peers &);

    private:

        STATE state;
        QHostAddress host;
        int port;
        std::list<char*> data;
};

#endif // PEERS_H
