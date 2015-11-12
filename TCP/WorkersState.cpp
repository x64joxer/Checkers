#include "TCP/WorkersState.h"

WorkersState::WorkersState(QObject *parent)
             : QObject(parent),
               messageState(MessageState::NONE_OK),
               timeout(false)
{

}

void WorkersState::SetPeer(QHostAddress ho, int po)
{
    host = ho;
    port = po;
}

void WorkersState::SetOKExpected(std::string id, std::string jId, MessageState state)
{
    messageState = state;
    timeout = ProgramVariables::GetSecondsSinceEpoch();
    waitForOKMessageID = id;
    jobId = jobId;
}

void WorkersState::SetNone()
{
    waitForOKMessageID = "";
    messageState = NONE_OK;
}

bool WorkersState::GetTimeout()
{
    if (messageState != NONE_OK)
    {
        if (ProgramVariables::GetSecondsSinceEpoch() - timeout > ProgramVariables::GetMaxTimeWaitToServer() / 1000) return 1;
    }

    return 0;
}

WorkersState::~WorkersState()
{

}
