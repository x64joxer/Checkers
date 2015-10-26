#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"

class MessageHandler
{
    public:
        MessageHandler();
        ServerTCP *server;
        PeerQueue *peerQueue;
        void Start();

    private:


};

#endif // MESSAGEHANDLER_H
