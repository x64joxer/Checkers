#ifndef MESSAGEFORWARDER_H
#define MESSAGEFORWARDER_H

#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"
#include "TCP/Peers.h"

class MessageForwarder : public QObject
{
        Q_OBJECT
    public:
        explicit MessageForwarder(QObject *parent = 0);
        void SetPeerQueue(PeerQueue *wsk) { peers = wsk; }
        void SetServer(ServerTCP *wsk) { server = wsk; }
    signals:

    public slots:
            void Start();

    private:
            ServerTCP *server;
            PeerQueue *peers;
};

#endif // MESSAGEFORWARDER_H
