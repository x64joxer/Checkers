#ifndef PEERQUEUE_H
#define PEERQUEUE_H

#include <list>
#include <QHostAddress>
#include "Traces/Traces.h"
#include "TCP/Peers.h"

class PeerQueue
{
    public:
        PeerQueue();
        void AddPeer(QHostAddress ho, int po);
        void RemovePeer(QHostAddress ho, int po);
        bool PeerExist(QHostAddress ho, int po);
    private:
        std::list<Peers> peers;

};

#endif // PEERQUEUE_H
