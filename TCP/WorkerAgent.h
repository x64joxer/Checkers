#ifndef WORKERAGENT_H
#define WORKERAGENT_H

#include "TCP/PeerQueue.h"
#include "TCP/PeerQueue.h"
#include "TCP/ServerTCP.h"
#include "TCP/MessageForwarder.h"

class WorkerAgent : public QObject
{
        Q_OBJECT
    public:
        explicit WorkerAgent(QObject *parent = 0);

        static void Init();
        static Peers First() { return peerQueue.First(); }
        static bool Empty() { return peerQueue.Empty(); }
        static void SendMessage(QHostAddress ho, int po, char* data) { messageForwarder.SendMessage( ho, po, data); }
        static void GetFirstMessage(QHostAddress &ho, int &po,char *data) { peerQueue.GetFirstMessage(ho,po,data); }
        static bool IsWaitingMessage() { return peerQueue.IsWaitingMessage(); }
    signals:

    public slots:

    private:
        static PeerQueue  peerQueue;
        static MessageForwarder messageForwarder;
        static ServerTCP server;


};

#endif // WORKERAGENT_H
