#ifndef WORKERSSTATE_H
#define WORKERSSTATE_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include <atomic>
#include <iostream>
#include "ProgramVariables.h"



class WorkersState : public QObject
{
        Q_OBJECT
    public:
        explicit WorkersState(QObject *parent = 0);
        ~WorkersState();
        enum MessageState { NONE_OK, START_WORK_OK };
        void SetPeer(QHostAddress ho, int po);        
        void SetOKExpected(std::string id, std::string jId, MessageState state);
        void SetNone();
        bool GetTimeout();
        std::string GetJobId() { return jobId; }

        std::string GetID() { return waitForOKMessageID; }
        MessageState GetState() { return messageState; }
        QHostAddress GetHost() { return host; }
        int GetPort() { return port; }
        static unsigned int GetGlobNumOfWaitingTimer() { return globNumOfWaitingTimer; }

    private:
        void StartTimer();
        QHostAddress host;
        int port;
        unsigned long long timeout;

        std::string waitForOKMessageID;
        std::string jobId;
        std::thread timerThread;
        MessageState messageState;

        static unsigned int globNumOfWaitingTimer;
        static std::mutex guard;

};
#endif // WORKERSSTATE_H
