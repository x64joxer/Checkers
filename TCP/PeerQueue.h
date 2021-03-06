#ifndef PEERQUEUE_H
#define PEERQUEUE_H

#include <QHostAddress>
#include <mutex>
#include <list>
#include <condition_variable>
#include "Traces/Traces.h"
#include "TCP/Peers.h"
#include "TCP/ServerTCP.h"
#include "TCP/Peers.h"
#include "ProgramVariables.h"

class ServerTCP;

class PeerQueue
{
    public:
        PeerQueue();
        void AddPeer(QHostAddress ho, int po);
        void RemovePeer(QHostAddress ho, int po);
        void AddData(QHostAddress ho, int po,char *data);     
        void SetServer(ServerTCP *serv) { server = serv; }
        Peers First() { return peers.front(); }
        Peers AT(const unsigned int n);
        unsigned int Size() { return peers.size(); }
        bool Empty() { return peers.empty(); }
        void GetFirstMessage(QHostAddress &ho, int &po,char *data);
        void GetFirstFreePeers(QHostAddress &ho, int &po);
        bool Exist(QHostAddress ho, int po);
        bool IsWaitingMessage() { if (waitingMessages>0) { return 1; } return 0; }
        unsigned int GetFreeStateNumber();
        unsigned int GetBusyStateNumber();

        void SetState(const QHostAddress ho, const int po, const Peers::STATE state);
        void SetNumberOfThread(const QHostAddress ho, const int po, unsigned short val);

    private:
        void GetData(QHostAddress ho, int po,char *data);
        bool PeerExist(QHostAddress ho, int po);
        std::list<Peers> peers;
        std::list<Peers*> messagesQueue;
        unsigned int waitingMessages;
        ServerTCP *server;
        std::mutex mutex_guard;
        unsigned int freePeers;
        unsigned int busyPeers;
        std::condition_variable *condition_var;

};

#endif // PEERQUEUE_H
