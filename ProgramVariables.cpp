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

unsigned short ProgramVariables::maxNumbeOfThreads = ProgramVariables::InitMaxThreads();
unsigned short ProgramVariables::numbeOfThreads = ProgramVariables::maxNumbeOfThreads;
