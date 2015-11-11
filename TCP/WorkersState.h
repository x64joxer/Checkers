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
        enum MessageState { NONE_OK, STATE_OK, BEST_RESULT_OK };
        void SetPeer(QHostAddress ho, int po);
        void SetOKExpected(std::string id, MessageState state);
        void SetNone();
        bool GetTimeout();
        std::string GetID() { return waitForOKMessageID; }
        MessageState GetState() { return messageState; }


    private:
        QHostAddress host;
        int port;
        unsigned long timeout;

        std::string waitForOKMessageID;
        MessageState messageState;

};
#endif // WORKERSSTATE_H
