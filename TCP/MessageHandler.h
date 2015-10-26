#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"

class MessageHandler
{
    public:
        MessageHandler();        
        void Start();
        void SetPeerQueue(PeerQueue *wsk) { peerQueue = wsk; }

    private:
        PeerQueue *peerQueue;

};

#endif // MESSAGEHANDLER_H
