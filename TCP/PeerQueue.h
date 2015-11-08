#ifndef PEERQUEUE_H
#define PEERQUEUE_H

#include <QHostAddress>
#include <mutex>
#include <list>
#include "Traces/Traces.h"
#include "TCP/Peers.h"
#include "TCP/ServerTCP.h"
#include "TCP/Peers.h"

class ServerTCP;

class PeerQueue
{
    public:
        PeerQueue();
        void AddPeer(QHostAddress ho, int po);
        void RemovePeer(QHostAddress ho, int po);
        void AddData(QHostAddress ho, int po,char *data);
        void SendMessage(QHostAddress ho, int po, char* data);        
        void SetServer(ServerTCP *serv) { server = serv; }
        Peers First() { return peers.front(); }
        bool Empty() { return peers.empty(); }
        void GetFirstMessage(QHostAddress &ho, int &po,char *data);
        bool IsWaitingMessage() { if (waitingMessages>0) { return 1; } return 0; }

        void SetState(const QHostAddress ho, const int po, const Peers::STATE state);

    private:
        void GetData(QHostAddress ho, int po,char *data);
        bool PeerExist(QHostAddress ho, int po);
        std::list<Peers> peers;
        unsigned int waitingMessages;
        ServerTCP *server;
        std::mutex mutex_guard;
        unsigned int freePeers;

};

#endif // PEERQUEUE_H
