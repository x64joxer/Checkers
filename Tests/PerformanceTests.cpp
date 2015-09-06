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
    qDebug() << "PerformanceTests::Test01()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();

    Traces::TurnOffTraces();

    unsigned long int result[4];

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
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
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 20000);
            result[numOfThreads-1] = Traces::GetCurrentTime();
        };
    };

    for (int i=1;i<4;i++)
    {
        qDebug() << "Nuber of threads: " << i+1 << " result" << double(result[0])/ double(result[i]);
    };

    delete board;
}
