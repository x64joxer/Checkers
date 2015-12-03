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

void WorkersState::SetOKExpected(const std::string & id, const std::string & jId, const MessageState state)
{
    std::lock_guard<std::mutex> lockGuard(guard);

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
    std::lock_guard<std::mutex> lockGuard(guard);
    waitForOKMessageID = "";    
    if (messageState != NONE_OK)
    {
        if (globNumOfWaitingTimer > 0) globNumOfWaitingTimer--;
    }
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
    guard.lock();
    if (messageState != NONE_OK) ++globNumOfWaitingTimer;
    guard.unlock();
    ProgramVariables::NotifyOne();
}

WorkersState::~WorkersState()
{

}


unsigned int WorkersState::globNumOfWaitingTimer = 0;
std::mutex WorkersState::guard;
