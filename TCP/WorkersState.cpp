#include "TCP/WorkersState.h"

WorkersState::WorkersState(QObject *parent)
             : QObject(parent),
               messageState(WorkerTCP::MessageState::NONE_OK)
{
    waitForOKMessageTimer = new QTimer();
    connect(waitForOKMessageTimer, SIGNAL(timeout()), this, SLOT(EmitNoResponse()));
}

void WorkersState::SetPeer(QHostAddress ho, int po)
{
    host = ho;
    port = po;
}

void WorkersState::SetOKExpected(std::string id, WorkerTCP::MessageState state)
{
    messageState = state;
    waitForOKMessageID = id;
    waitForOKMessageTimer->setInterval(ProgramVariables::GetMaxTimeWaitToServer());
    waitForOKMessageTimer->start();
}

void WorkersState::EmitNoResponse()
{
    emit NoResponseFromWorker(host, port);
}

WorkersState::~WorkersState()
{
    delete waitForOKMessageTimer;
}
