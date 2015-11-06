#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"
#include "TCP/MessageForwarder.h"
#include "TCP/WorkerAgent.h"
#include "TCP/MessageCoder.h"
#include "TCP/Peers.h"

class MessageHandler
{
    public:
        MessageHandler();        
        void Start();
        void SetPeerQueue(PeerQueue *wsk) { peerQueue = wsk; }
        void SetMessageForwarder(MessageForwarder *wsk) { messageForwarder = wsk; }

    private:
        void MessageInterpreting(const QHostAddress ho, const int po, const std::map<std::string, std::string> data);
        void TakeSetState(const QHostAddress ho, const int po, const std::map<std::string, std::string> data);


        PeerQueue *peerQueue;
        MessageForwarder *messageForwarder;

};

#endif // MESSAGEHANDLER_H
