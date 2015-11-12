#ifndef WORKERSSTATE_H
#define WORKERSSTATE_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
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

    private:
        QHostAddress host;
        int port;
        unsigned long timeout;

        std::string waitForOKMessageID;
        std::string jobId;
        MessageState messageState;

};
#endif // WORKERSSTATE_H
