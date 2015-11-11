#include "TCP/WorkersState.h"

WorkersState::WorkersState(QObject *parent)
             : QObject(parent),
               messageState(MessageState::NONE_OK),
               timeout(false)
{
    waitForOKMessageTimer = new QTimer();
    connect(waitForOKMessageTimer, SIGNAL(timeout()), this, SLOT(NoResponse()));
}

void WorkersState::SetPeer(QHostAddress ho, int po)
{
    host = ho;
    port = po;
}

void WorkersState::SetOKExpected(std::string id, MessageState state)
{
    messageState = state;
    timeout = false;
    waitForOKMessageID = id;
    waitForOKMessageTimer->setInterval(ProgramVariables::GetMaxTimeWaitToServer());
    waitForOKMessageTimer->start();
}

void WorkersState::NoResponse()
{
    timeout = true;
}

WorkersState::~WorkersState()
{
    delete waitForOKMessageTimer;
}
