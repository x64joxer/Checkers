#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <atomic>
#include "Traces/Traces.h"
#include "TCP/ServerTCP.h"
#include "TCP/PeerQueue.h"
#include "TCP/MessageForwarder.h"
#include "TCP/WorkerAgent.h"
#include "TCP/MessageCoder.h"
#include "TCP/Peers.h"
#include "ThreadIA/ThreadIABoardQueue.h"
#include "ProgramVariables.h"
#include "TCP/WorkersState.h"

class MessageHandler
{
    public:
        MessageHandler();        
        void Start();        
        void SetMessageForwarder(MessageForwarder *wsk) { messageForwarder = wsk; }
        void SetBoardQueue(ThreadIABoardQueue<900000> *wsk);
        void StartSharing(unsigned long time) { startTime = time; shareJobs = true; }
        void StopSharing() { shareJobs = false; }

    private:
        void MessageInterpreting(const QHostAddress ho, const int po, const std::map<std::string, std::string> data);
        void TakeSetState(const QHostAddress ho, const int po, const std::map<std::string, std::string> data);
        void TakeBestResult(const QHostAddress ho, const int po, const std::map<std::string, std::string> data);

        MessageForwarder *messageForwarder;
        ThreadIABoardQueue<900000> *boardQueue;
        std::atomic<bool> shareJobs;
        unsigned long startTime;
        std::map<std::string, WorkersState*> workersState;
};

#endif // MESSAGEHANDLER_H
