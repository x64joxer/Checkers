#ifndef WORKERSSTATE_H
#define WORKERSSTATE_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include "ProgramVariables.h"
#include "TCP/WorkerTCP.h"

class WorkersState : public QObject
{
        Q_OBJECT
    public:
        explicit WorkersState(QObject *parent = 0);
        ~WorkersState();
        void SetPeer(QHostAddress ho, int po);
        void SetOKExpected(std::string id, WorkerTCP::MessageState state);
        WorkerTCP::MessageState GetState() { return messageState; }

    signals:
        void NoResponseFromWorker(QHostAddress ho, int po);

    private slots:
        void EmitNoResponse();

    private:
        QHostAddress host;
        int port;

        QTimer *waitForOKMessageTimer;
        std::string waitForOKMessageID;
        WorkerTCP::MessageState messageState;
};

#endif // WORKERSSTATE_H
