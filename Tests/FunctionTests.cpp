#include "Tests/FunctionTests.h"

FunctionTests::FunctionTests()
{

}

void FunctionTests::Make()
{
    Test01();
}

void FunctionTests::Test01()
{
    Traces() << "\n" << "FunctionTests::Test01()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();
    Board wrongBoard;

    wrongBoard =

    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |") +
    std::string("| | | | | | | | |");


    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test01() for number of thread = " << numOfThreads;

        *board =
                    std::string("| |w| |w| |w| |w|") +
                    std::string("|w| |w| |w| |w| |") +
                    std::string("| | | |w| |w| |w|") +
                    std::string("|w| | | | | | | |") +
                    std::string("| |b| | | | | | |") +
                    std::string("|b| | | |b| |b| |") +
                    std::string("| |b| |b| |b| |b|") +
                    std::string("|b| |b| |b| |b| |");

        {
            ThreadIAMove<900000> worker;
            Traces::TurnOffTraces();
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000);
            Traces::TurnOnTraces();
        };

        if (*board == wrongBoard)
        {
            Traces() << "\n" << "ERROR: Test01() Wrong result for number of threads = " << numOfThreads;
            board->printDebug();

        };
    };

    Traces() << "\n" << "LOG: End Test01()";

    Traces::TurnOffTraces();

    delete board;
}

