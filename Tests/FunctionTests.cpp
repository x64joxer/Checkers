#include "Tests/FunctionTests.h"

FunctionTests::FunctionTests()
{

}

void FunctionTests::Make()
{
    Test01();
    Test02();
    Test03();
    Test04();
    Test05();
    Test06();
    Test07();
    Test08();
    Test09();
}

void FunctionTests::Test01()
{
    Traces() << "\n" << "FunctionTests::Test01()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();
    Board goodBoard;

    goodBoard =

            std::string("| |w| |w| |w| |w|") +
            std::string("|w| |w| |w| |w| |") +
            std::string("| | | |w| |w| |w|") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("|b| |w| |b| |b| |") +
            std::string("| |b| |b| |b| |b|") +
            std::string("|b| |b| |b| |b| |");


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
            ThreadIAMove<3000000> worker;
            //Traces::TurnOffTraces();
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);
            //Traces::TurnOnTraces();
        };

        if (*board != goodBoard)
        {
            Traces() << "\n" << "ERROR: Test01() Wrong result for number of threads = " << numOfThreads;
            board->PrintDebug();

        };
    };

    TRACE01 Traces() << "\n" << "LOG: End Test01()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test02()
{
    Traces() << "\n" << "FunctionTests::Test02()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();
    Board goodBoard;

    goodBoard =

            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | |W| | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("|w| | | | | | | |") +
            std::string("| | | | | | | |w|") +
            std::string("|b| | | | | | | |");


    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test02() for number of thread = " << numOfThreads;

        *board =
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | | |B| | | |") +
                std::string("| | | | | | | | |") +
                std::string("|w| | | |b| | | |") +
                std::string("| | | |W| | | |w|") +
                std::string("|b| | | | | | | |");
        {
            ThreadIAMove<3000000> worker;

            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);

        };

        if (*board != goodBoard)
        {
            Traces() << "\n" << "ERROR: Test02() Wrong result for number of threads = " << numOfThreads;
            board->PrintDebug();
            goodBoard.PrintDebug();

        };
    };

    TRACE01 Traces() << "\n" << "LOG: End Test02()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test03()
{
    Traces() << "\n" << "FunctionTests::Test03()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();
    Board goodBoard;

    goodBoard =

            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | |W| | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | |w|") +
            std::string("| | |W| | | | | |");


    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test03() for number of thread = " << numOfThreads;

        *board =
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | |W| | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("|w| | | | | | | |") +
                std::string("| |b| | | | | |w|") +
                std::string("| | | | | | | | |");
        {
            ThreadIAMove<3000000> worker;

            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);

        };

        if (*board != goodBoard)
        {
            Traces() << "\n" << "ERROR: Test03() Wrong result for number of threads = " << numOfThreads;
            board->PrintDebug();
            goodBoard.PrintDebug();

        };
    };

    TRACE01 Traces() << "\n" << "LOG: End Test03()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test04()
{
    Traces() << "\n" << "FunctionTests::Test04()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();
    Board goodBoard;
    Board goodBoard_2;

    goodBoard =
    std::string("| |w| |w| | | |w|") +
    std::string("|w| | | |w| |w| |") +
    std::string("| | | | | |w| |w|") +
    std::string("| | | | | | | | |") +
    std::string("| |b| | | |w| | |") +
    std::string("|b| | | | | |b| |") +
    std::string("| |b| | | |b| |b|") +
    std::string("|b| | | |b| |b| |");

    goodBoard_2 =
    std::string("| |w| |w| | | |w|") +
    std::string("|w| | | |w| |w| |") +
    std::string("| | | |w| | | |w|") +
    std::string("| | | | | | | | |") +
    std::string("| |b| |w| | | | |") +
    std::string("|b| | | | | |b| |") +
    std::string("| |b| | | |b| |b|") +
    std::string("|b| | | |b| |b| |");

    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test04() for number of thread = " << numOfThreads;

        *board =
                std::string("| |w| |w| | | |w|") +
                std::string("|w| | | |w| |w| |") +
                std::string("| | | |w| |w| |w|") +
                std::string("| | | | |b| | | |") +
                std::string("| |b| | | | | | |") +
                std::string("|b| | | | | |b| |") +
                std::string("| |b| | | |b| |b|") +
                std::string("|b| | | |b| |b| |");
        {
            ThreadIAMove<3000000> worker;

            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);

        };

        if ((*board != goodBoard)&&(*board != goodBoard_2))
        {
            Traces() << "\n" << "ERROR: Test04() Wrong result for number of threads = " << numOfThreads;
            board->PrintDebug();
            goodBoard.PrintDebug();
        };
    };

    TRACE01 Traces() << "\n" << "LOG: End Test04()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test05()
{
    Traces() << "\n" << "FunctionTests::Test05()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();

    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test05() for number of thread = " << numOfThreads;

        *board =
            std::string("| |B| | | | | |w|") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | |w|") +
            std::string("| | | | |w| | | |") +
            std::string("| | | | | | | |b|") +
            std::string("| | |w| | | | | |") +
            std::string("| | | | | | | |b|") +
            std::string("|b| | | |b| | | |");

        {
            ThreadIAMove<3000000> worker;
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);
        };

    };

    TRACE01 Traces() << "\n" << "LOG: End Test05()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test06()
{
    Traces() << "\n" << "FunctionTests::Test06()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();

    Traces::TurnOnTraces();

    for (unsigned short numOfThreads=1;numOfThreads<5;numOfThreads++)
    {
        Traces() << "\n" << "FunctionTests::Test06() for number of thread = " << numOfThreads;

        *board =
                std::string("| | | | | | | |w|") +
                std::string("| | |B| | | | | |") +
                std::string("| | | | | | | |w|") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | |b| |b|") +
                std::string("|b| |w| | | |b| |") +
                std::string("| | | | | | | | |") +
                std::string("|b| |b| |b| | | |");

        {
            ThreadIAMove<3000000> worker;
            worker(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 3000, 1000, KindOfSteps::Step);
        };

    };

    TRACE01 Traces() << "\n" << "LOG: End Test06()";

    Traces::TurnOffTraces();

    delete board;
}

void FunctionTests::Test07()
{
    Traces::TurnOnTraces();

    Traces() << "\n" << "FunctionTests::Test07()";

    Board *board = new Board();

    Board board1;
    Board board2;
    Board board3;
    Board board4;
    Board board5;
    Board board6;
    Board board7;

          board1 = std::string("| |w| |w| |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board2 = std::string("| | | |w| |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board3 = std::string("| |w| | | |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board4 = std::string("| |w| |w| | | |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board5 = std::string("| |w| |w| |w| | |") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board6 = std::string("| |w| |w| |w| |w|") +
                   std::string("| | |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board7 = std::string("| |w| |w| |w| |w|") +
                   std::string("|w| | | |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

    ThreadIABoardQueue<5> testQueue;

    Traces() << "\n" << "LOG: Push back board 1";
    testQueue.PushBack(board1);
    Traces() << "\n" << "LOG: Push back board 2";
    testQueue.PushBack(board2);
    Traces() << "\n" << "LOG: Push back board 3";
    testQueue.PushBack(board3);
    Traces() << "\n" << "LOG: Push back board 4";
    testQueue.PushBack(board4);

    Traces() << "\n" << "LOG: Pop front board 1";
    testQueue.PopFront(0);
    Traces() << "\n" << "LOG: Pop front board 2";
    testQueue.PopFront(0);
    Traces() << "\n" << "LOG: Pop front board 3";
    testQueue.PopFront(0);

    Traces() << "\n" << "LOG: Push back board 5";
    testQueue.PushBack(board5);
    Traces() << "\n" << "LOG: Push back board 6";
    testQueue.PushBack(board6);
    Traces() << "\n" << "LOG: Push back board 7";
    testQueue.PushBack(board7);

    Traces() << "\n" << "LOG: Pop front board 4";
    testQueue.PopFront(0);
    Traces() << "\n" << "LOG: Pop front board 5";
    testQueue.PopFront(0);
    Traces() << "\n" << "LOG: Pop front board 6";
    testQueue.PopFront(0);
    Traces() << "\n" << "LOG: Pop front board 7";
    *board = testQueue.PopFront(0);

    if (*board != board7)
    {
        Traces() << "\n" << "ERR: End Test07()  Wrong result";
        board->PrintDebug();
    }

    Traces() << "\n" << "LOG: End Test07()";

    delete board;
}

void FunctionTests::Test08()
{
    Traces::TurnOnTraces();

    Traces() << "\n" << "FunctionTests::Test08()";

    Board *board = new Board();

    Board board1;
    Board board2;
    Board board3;
    Board board4;
    Board board5;
    Board board6;
    Board board7;

          board1 = std::string("| |w| |w| |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board2 = std::string("| | | |w| |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board3 = std::string("| |w| | | |w| |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board4 = std::string("| |w| |w| | | |w|") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board5 = std::string("| |w| |w| |w| | |") +
                   std::string("|w| |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board6 = std::string("| |w| |w| |w| |w|") +
                   std::string("| | |w| |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

          board7 = std::string("| |w| |w| |w| |w|") +
                   std::string("|w| | | |w| |w| |") +
                   std::string("| |w| |w| |w| |w|") +
                   std::string("| | | | | | | | |") +
                   std::string("| | | | | | | | |") +
                   std::string("|b| |b| |b| |b| |") +
                   std::string("| |b| |b| |b| |b|") +
                   std::string("|b| |b| |b| |b| |");

    ThreadIABoardQueue<5> testQueue;

    Traces() << "\n" << "LOG: Push back board 1";
    testQueue.PushBack(board1);
    Traces() << "\n" << "LOG: Push back board 2";
    testQueue.PushBack(board2);
    Traces() << "\n" << "LOG: Push back board 3";
    testQueue.PushBack(board3);
    Traces() << "\n" << "LOG: Push back board 4";
    testQueue.PushBack(board4);

    Traces() << "\n" << "LOG: Pop front board 1";
    testQueue.First(true);
    Traces() << "\n" << "LOG: Pop front board 2";
    testQueue.First(true);
    Traces() << "\n" << "LOG: Pop front board 3";
    testQueue.First(true);

    Traces() << "\n" << "LOG: Push back board 5";
    testQueue.PushBack(board5);
    Traces() << "\n" << "LOG: Push back board 6";
    testQueue.PushBack(board6);
    Traces() << "\n" << "LOG: Push back board 7";
    testQueue.PushBack(board7);

    Traces() << "\n" << "LOG: Pop front board 4";
    testQueue.First(true);
    Traces() << "\n" << "LOG: Pop front board 5";
    testQueue.First(true);
    Traces() << "\n" << "LOG: Pop front board 6";
    testQueue.First(true);
    Traces() << "\n" << "LOG: Pop front board 7";
    *board = testQueue.PopFront(0);

    if (*board != board7)
    {
        Traces() << "\n" << "ERR: End Test08()  Wrong result";
        board->PrintDebug();
    }

    Traces() << "\n" << "LOG: End Test08()";

    delete board;
}

void FunctionTests::Test09()
{
    Traces() << "\n" << "FunctionTests::Test09()";
    std::atomic_bool endIaJobFlag;
    std::atomic<int> currentPercentOfSteps;
    Board *board = new Board();

    Traces::TurnOnTraces();

    unsigned short numOfThreads=4;
        Traces() << "\n" << "FunctionTests::Test09() for number of thread = ";

       *board  = std::string("| |w| | | |w| |w|") +
                 std::string("|w| |w| |w| |w| |") +
                 std::string("| |w| |w| |w| |w|") +
                 std::string("| | | | | | | | |") +
                 std::string("| | | | | | | | |") +
                 std::string("|b| |b| |b| |b| |") +
                 std::string("| |b| |b| |b| |b|") +
                 std::string("|b| |b| |b| |b| |");

    {

        unsigned short movments = 0;

        while ((board->GetNumberOfBlack() > 0) && (board->GetNumberOfWhite() > 0))
        {
                board->StartWhite();
                Traces() << "\n" << "Step number " << movments;
                board->PrintDebug();

                if (board->GetNumberOfWhite() > 0)
                {
                    ThreadIAMove<3000000> workerA;
                    workerA(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 100, 10, KindOfSteps::Time);
                }

                movments++;

                board->Mirror();
                board->StartWhite();
                Traces() << "\n" << "Step number " << movments;
                board->PrintDebug();

                if (board->GetNumberOfBlack() > 0)
                {
                    ThreadIAMove<3000000> workerB;
                    workerB(board, &endIaJobFlag, &currentPercentOfSteps, numOfThreads, 100, 10, KindOfSteps::Time);
                }

                movments++;
                if (movments > 100) break;
        }
    }
    TRACE01 Traces() << "\n" << "LOG: End Test09()";

    Traces::TurnOffTraces();

    delete board;
}
