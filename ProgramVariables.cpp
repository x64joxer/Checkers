#include "ProgramVariables.h"

ProgramVariables::ProgramVariables()
{

}

unsigned short ProgramVariables::InitMaxThreads()
{
    maxNumbeOfThreads = std::thread::hardware_concurrency();

    if (maxNumbeOfThreads == 0)
    {
        maxNumbeOfThreads = 1;
    };    

    return maxNumbeOfThreads;
}

unsigned short ProgramVariables::GetMaxNumberOfThreads()
{
    return maxNumbeOfThreads;
}

void ProgramVariables::SetNumberOfThreads(const unsigned short num)
{
    numbeOfThreads = num;
}

unsigned short ProgramVariables::GetNumberOfThreads()
{
    return numbeOfThreads;
}


bool ProgramVariables::IsWorker()
{
    return isWorker;
}

void ProgramVariables::SetWorker(const bool flag)
{
    isWorker = flag;
}

unsigned long ProgramVariables::GetSecondsSinceEpoch()
{
    std::time_t result = std::time(nullptr);

    return result;
}

unsigned long ProgramVariables::GetMaxTimeWaitToWorkers()
{
    return 5;
}

unsigned long ProgramVariables::GetMaxTimeWaitToServer()
{
    return 3000;
}

QString ProgramVariables::GetServerIP()
{
    return "192.168.0.6";
}

int ProgramVariables::GetServerPort()
{
   return 6000;
}

std::condition_variable * ProgramVariables::GetGlobalConditionVariable()
{
    return &condition_var;
}

unsigned int ProgramVariables::GetRecconectingTime()
{
    return 5000;
}

unsigned short ProgramVariables::GetMaxNumberOfReattempt()
{
    return 2;
}

std::string ProgramVariables::CreateMessageId()
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    return std::to_string(++messageId);
}

unsigned long ProgramVariables::GetMaxSecondsToEnd()
{
    return 3;
}

unsigned long ProgramVariables::GetMaxTimeForIa()
{
    return 5;
}

bool ProgramVariables::isWorker = false;
unsigned short ProgramVariables::maxNumbeOfThreads = ProgramVariables::InitMaxThreads();
unsigned short ProgramVariables::numbeOfThreads = ProgramVariables::maxNumbeOfThreads;
unsigned long ProgramVariables::messageId = 0;
std::mutex ProgramVariables::mutex_guard;
std::condition_variable ProgramVariables::condition_var;
unsigned long ProgramVariables::numOfAnalysded = 0;
