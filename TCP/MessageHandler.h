#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"
#include "TCP/MessageForwarder.h"

class MessageHandler
{
    public:
        MessageHandler();        
        void Start();
        void SetPeerQueue(PeerQueue *wsk) { peerQueue = wsk; }
        void SetMessageForwarder(MessageForwarder *wsk) { messageForwarder = wsk; }

    private:
        PeerQueue *peerQueue;
        MessageForwarder *messageForwarder;

};

#endif // MESSAGEHANDLER_H
