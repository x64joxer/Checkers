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
        ~Peers();
        void SetPeer(QHostAddress ho, int po);
        QHostAddress GetHost();
        int GetPort();
        void AddData(char *dat);
        void GetData(char *dat);
        bool IsData() { return !data.empty(); }
        unsigned int NumberOfMessages() const { return data.size(); }
        bool IsNull() const { return isNull; }
        void SetNull (const bool flag) { isNull = flag; }

        enum  STATE { NONE, BUSY, FREE };

        STATE GetState() const;
        void SetState(const STATE val);

        unsigned short GetNumOThread() const { return numOfThread; }
        void SetNumOThread(const unsigned short val) { numOfThread = val; }

        bool operator==(const Peers &);

    private:

        bool isNull;
        STATE state;
        QHostAddress host;
        int port;
        std::list<char*> data;

        unsigned short numOfThread;
};

#endif // PEERS_H
