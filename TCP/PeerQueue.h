#ifndef PEERQUEUE_H
#define PEERQUEUE_H

#include <list>
#include <QHostAddress>
#include "Traces/Traces.h"
#include "TCP/Peers.h"
#include "TCP/ServerTCP.h"

class ServerTCP;

class PeerQueue
{
    public:
        PeerQueue();
        void AddPeer(QHostAddress ho, int po);
        void RemovePeer(QHostAddress ho, int po);
        void AddData(QHostAddress ho, int po,char *data);
        void GetData(QHostAddress ho, int po,char *data);
        void SendMessage(QHostAddress ho, int po, char* data);
        bool PeerExist(QHostAddress ho, int po);
        void SetServer(ServerTCP *serv) { server = serv; }
        Peers First() { return peers.front(); }
        bool Empty() { return peers.empty(); }
    private:
        std::list<Peers> peers;
        ServerTCP *server;

};

#endif // PEERQUEUE_H
