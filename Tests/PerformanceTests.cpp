#include "Tests/PerformanceTests.h"

PerformanceTests::PerformanceTests()
{

}

void PerformanceTests::Make()
{
    Test01();
}

void PerformanceTests::Test01()
{
    Traces::TurnOnTraces();
    Traces() << "\n" << "PerformanceTests::Test01()";
    Traces::TurnOffTraces();

    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();

    Traces::TurnOffTraces();

    unsigned long int result[ProgramVariables::GetMaxNumberOfThreads()];

    for (unsigned short numOfThreads=1;numOfThreads<=ProgramVariables::GetMaxNumberOfThreads();numOfThreads++)
    {
        *board =
                    std::string("| |w| |w| |w| |w|") +
                    std::string("|w| |w| |w| |w| |") +
                    std::string("| |w| |w| |w| |w|") +
                    std::string("| | | | | | | | |") +
                    std::string("| |b| | | | | | |") +
                    std::string("| | |b| |b| |b| |") +
                    std::string("| |b| |b| |b| |b|") +
                    std::string("|b| |b| |b| |b| |");

        {
            ThreadIAMove<900000> worker;
            Traces::GetCurrentTime();
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 20000, KindOfSteps::Step);
            result[numOfThreads-1] = Traces::GetCurrentTime();
        };    
    };

    Traces::TurnOnTraces();
    Traces() << "\n" << "LOG: Performance result:";

    for (int i=1;i<ProgramVariables::GetMaxNumberOfThreads();i++)
    {
        Traces() << "\n" << "LOG: Number of threads: " << i+1 << " result: " << QString::number(double(result[0])/ double(result[i]));
    };
    Traces::TurnOffTraces();

    delete board;
}
