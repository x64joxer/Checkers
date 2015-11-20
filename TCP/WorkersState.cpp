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
    jobId = jId;
    std::thread tempThread(&WorkersState::StartTimer, this);
    timerThread = std::move(tempThread);
    timerThread.detach();
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

void WorkersState::StartTimer()
{
    std::chrono::seconds dura( ProgramVariables::GetMaxTimeWaitToWorkers() );
    std::this_thread::sleep_for(dura);
    ProgramVariables::GetGlobalConditionVariable()->notify_all();
}

WorkersState::~WorkersState()
{

}
