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
    return 3;
}

unsigned long ProgramVariables::GetMaxSecondsToEnd()
{
    return 3;
}

bool ProgramVariables::isWorker = false;
unsigned short ProgramVariables::maxNumbeOfThreads = ProgramVariables::InitMaxThreads();
unsigned short ProgramVariables::numbeOfThreads = ProgramVariables::maxNumbeOfThreads;
