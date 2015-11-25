#include "ThreadIA/ThreadIATreeExpander.h"

template <unsigned long long MQueue, unsigned long long sQueue>
ThreadIATreeExpander<MQueue, sQueue>::ThreadIATreeExpander() :
    queueSize(sQueue),
    lastQueueElement(0),
    firstQueueElement(0),    
    doNotForgetQueueSize(sQueue/50),
    lastDoNotForgetQueueElement(0),
    numberOfElements(0)

{

}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::ExpandWithoutQueue(unsigned int howManySteps, unsigned int frequencyOfTransferData, const unsigned short numThread, std::atomic<int> *percentSteps, KindOfSteps stepKind)
{
    Expand(howManySteps, frequencyOfTransferData, *mainBoardQueue_2, numThread, percentSteps, stepKind);
}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::SetMainBoardQueue(ThreadIABoardQueue<MQueue> * mainBoardQueue)
{
    mainBoardQueue_2 = mainBoardQueue;
}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::Expand(unsigned long long howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue, const unsigned short numThread, std::atomic<int> *percentSteps, KindOfSteps stepKind)
{
    TRACE01 Traces() << "\n" << "LOG: EXPAND START";
    TRACE01 Traces() << "\n" << "LOG: void ThreadIATreeExpander<MQueue, sQueue>::Expand(unsigned int howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue)";

    threadNumber = numThread;

    queue[0] = mainBoardQueue.PopFront(threadNumber);
    if (!queue[firstQueueElement].GetNullBoard()) numberOfElements++;

    unsigned long long step =0;
    unsigned long long totalStep = howManySteps;

    if (stepKind == KindOfSteps::Step)
    {
        step = 0;
    } else
    if (stepKind == KindOfSteps::Time)
    {
        step = ProgramVariables::GetSecondsSinceEpoch();
        howManySteps = step + howManySteps;
    }

    unsigned long long current;

    while (step < howManySteps)
    {
        if (queue[firstQueueElement].GetNullBoard()) break;

        for (current = firstQueueElement; current <= lastQueueElement; )
        {            

            //Expand current element
            if (queue[current].Black())
            {
              TRACE01 Traces() << "\n" << "LOG: (treePointer->Black())";
              firstQueueElement = current+1;
              numberOfElements--;
              ExpandBlack(queue[current], step);                            
            } else
            {
              TRACE01 Traces() << "\n" << "LOG: (treePointer->White())";
              firstQueueElement = current+1;
              numberOfElements--;
              ExpandWhite(queue[current], step);              
            };

            if (stepKind == KindOfSteps::Step)
            {
                TRACE01 Traces() << "\n" << "LOG: step++";
                step++;
            } else
            if (stepKind == KindOfSteps::Time)
            {
                step = ProgramVariables::GetSecondsSinceEpoch();
            }

            //Finish job
            if (step >= howManySteps) break;

            //Check if time to transfer data 

            if ((lastQueueElement>=firstQueueElement)||(lastQueueElement>queueSize-100)||(lastDoNotForgetQueueElement>(queueSize/50)-100))
            {
                if ((frequencyOfTransferData<=lastQueueElement-firstQueueElement)||(lastQueueElement>queueSize-100)||(lastDoNotForgetQueueElement>(queueSize/50)-100))
                {

                         TRACE01 Traces() << "\n" << "LOG:" << firstQueueElement;
                         TRACE01 Traces() << "\n" << "LOG:" << lastQueueElement;
                        TransferBoards(mainBoardQueue);
                        queue[0] = mainBoardQueue.PopFront(threadNumber);
                        current = 0;

                        if (queue[0].GetNullBoard())
                        {
                            TRACE01 Traces() << "\n" << "LOG: Everyone is waiting! No jobs";
                            break;
                        };
                        continue;
                };
            };

            ++current;

            //Update status
            if (numThread == 1)
            {
                if (percentSteps)
                {
                    if (stepKind == KindOfSteps::Step)
                    {
                        if (step == 0)
                        {
                            *percentSteps = (step+1) / (howManySteps / 100);
                        } else
                        {
                            *percentSteps = step / (howManySteps / 100);
                        }
                    } else
                    if (stepKind == KindOfSteps::Time)
                    {
                        *percentSteps = (totalStep - (howManySteps - step)) * (100 / totalStep);
                    }
                };
            };
        };

        if (queue[firstQueueElement].GetNullBoard())
        {
            TRACE01 Traces() << "\n" << "LOG: Everyone is waiting! No jobs";
            break;
        };

        TRACE01 Traces() << "\n" << "LOG: for (current = firstQueueElement; current <= lastQueueElement; ) END";

        //Finish job
        if (step >= howManySteps)
        {
            TRACE01 Traces() << "\n" << "LOG: (step >= howManySteps) finihing job!";
            break;
        };

        //No jobs take more from global queue
        if (step < howManySteps)
        {
            TRACE01 Traces() << "\n" << "LOG: No jobs. Taking fom global queue";

            TransferBoards(mainBoardQueue);
            queue[0] = mainBoardQueue.PopFront(threadNumber);

            if (queue[0].GetNullBoard())
            {
                TRACE01 Traces() << "\n" << "LOG: No job in global queue. Finishing thread.";
                break;
            };

            lastQueueElement =0;
            firstQueueElement =0;
        }

    };

    TRACE01 Traces() << "\n" << "LOG: Number of temporary queue array " << lastQueueElement;
    TransferBoards(mainBoardQueue);

    TRACE01 Traces() << "\n" << "LOG: EXPAND STOP";
    Traces::RemoveThreadID();
}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue)
{
    TRACE01 Traces() << "\n" << "LOG: ThreadIATreeExpander<MQueue, sQueue>::TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue)";
    TRACE01 Traces() << "\n" << "LOG: numberOfElements=" << numberOfElements;

    if (numberOfElements>0)
    {
        if (lastQueueElement>=firstQueueElement)
        {
            if ((lastQueueElement-firstQueueElement)+1>0)
            {
                for (unsigned long long i=firstQueueElement;i<=lastQueueElement;i++)
                {
                     TRACE01 Traces() << "\n" << "LOG: mainBoardQueue.PushBack(queue[i])";
                    mainBoardQueue.PushBack(queue[i]);
                };

                firstQueueElement =0;
                lastQueueElement=0;
            };
        };
    };

    if (lastDoNotForgetQueueElement>0)
    {
        for (unsigned long long i=1;i<=lastDoNotForgetQueueElement;i++)
        {
            mainBoardQueue.PushBackDoNotForget(queue[i]);
        };
       lastDoNotForgetQueueElement = 0;
    };

    mainBoardQueue.NotifyRest();
}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::AddToMainQueue(const Board &board)
{
    if (++lastQueueElement > queueSize-1)
    {
        Traces() << "\n" << "ERROR: No free memory cells in main queue";
    } else
    {
        queue[lastQueueElement] = board;
        TRACE01 Traces() << "\n" << "LOG: AddToMainQueue numberOfElements=" << numberOfElements;
        numberOfElements= numberOfElements + 1;
        TRACE01 Traces() << "\n" << "LOG: AddToMainQueue numberOfElements=" << numberOfElements;
    };
}

template <unsigned long long MQueue, unsigned long long sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::AddToDoNotForgetQueue(const Board &board)
{
    if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)
    {
        Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
    } else
    {
        doNotForgetQueue[lastDoNotForgetQueueElement] = board;
    };
}

template <unsigned long long MQueue, unsigned long long sQueue>
bool ThreadIATreeExpander<MQueue, sQueue>::ExpandWhite(Board board, unsigned int stepNumber)
{
    TRACE01 Traces() << "\n" << "LOG: void IATreeExpander::ExpandWhite(IADecisionTree *treePointer)";

    //DEL Board board = board.GetBoard();
    unsigned short pawnNumber = board.GetNumberOfWhite();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (board.GetPreviousMurder()<12)
    {
        if (board.GetNumberOfBlack() == 0)
        {
            AddToDoNotForgetQueue(board);

            TRACE01 Traces() << "\n" << "LOG: There was situation when all black was killed!";
            TRACE01 board.printDebug();
            return 0;
        };

        unsigned short i = board.GetPreviousMurder();
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;

           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (!board.GetWhitePatchEnd()) tempNew.SetOrigin(tempNew);           

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (!board.GetWhitePatchEnd()) tempNew.SetOrigin(tempNew);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (!board.GetWhitePatchEnd()) tempNew.SetOrigin(tempNew);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (!board.GetWhitePatchEnd()) tempNew.SetOrigin(tempNew);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
       };

       if (!killFlag)
       {           
           board.SetPreviousMurder(12);
           board.StartBlack();
           board.SetWhitePatchEnd(true);
           ExpandBlack(board);
       };

       return 0;
    };

    if (board.GetNumberOfWhite() == 0)
    {
        AddToDoNotForgetQueue(board);

        TRACE01 Traces() << "\n" << "LOG: There was situation when all white was killed!";
        TRACE01 board.printDebug();
        return 0;
    };

    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);           

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
       };
    };
    //If no kills check other steps
    if (!killFlag)
    {        
        TRACE01 Traces() << "\n" << "LOG:  (!killFlag) == true";
        bool canImove = false;
        board.SetWhitePatchEnd(true);

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {
            //Bottom Left
            if (possible.CheckPutBottomLeftWhite(i, board))
            {
                TRACE01 Traces() << "\n" << "LOG: possible.CheckPutBottomLeftWhite(" << i << ", board) == true";
                Board tempNew = board;
                TRACE01 tempNew.printDebug();
                tempNew.PutWhiteBottomLeftPawn(i);
                tempNew.StartBlack();
                tempNew.SetPreviousMurder(12);

                AddToMainQueue(tempNew);

                TRACE01 Traces() << "\n" << "LOG: Result";
                TRACE01 tempNew.printDebug();
                canImove = true;
            };
            //Bottom Right
            if (possible.CheckPutBottomRightWhite(i, board))
            {
                TRACE01 Traces() << "\n" << "LOG: possible.CheckPutBottomRightWhite(" << i << ", board) == true";
                Board tempNew = board;
                TRACE01 tempNew.printDebug();
                tempNew.PutWhiteBottomRightPawn(i);
                tempNew.StartBlack();
                tempNew.SetPreviousMurder(12);

                AddToMainQueue(tempNew);

                TRACE01 Traces() << "\n" << "LOG: Result";
                TRACE01 tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetWhitePawnPons(i))
            {
                //Top Left
                if (possible.CheckPutTopLeftWhite(i, board))
                {
                    TRACE01 Traces() << "\n" << "LOG: possible.CheckPutTopLeftWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    TRACE01 tempNew.printDebug();
                    tempNew.PutWhiteTopLeftPawn(i);

                    //TO DO if (board.IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartBlack();
                        tempNew.SetPreviousMurder(12);

                        AddToMainQueue(tempNew);

                        TRACE01 Traces() << "\n" << "LOG: Result";
                        TRACE01 tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     TRACE01 Traces() << "\n" << "LOG: There was similar white board!";
                    //TO DO };
                };
                //Top Right
                if (possible.CheckPutTopRightWhite(i, board))
                {
                    TRACE01 Traces() << "\n" << "LOG: possible.CheckPutTopRightWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    TRACE01 tempNew.printDebug();
                    tempNew.PutWhiteTopRightPawn(i);

                    //TO DO if (board.IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartBlack();
                        tempNew.SetPreviousMurder(12);

                        AddToMainQueue(tempNew);

                        TRACE01 Traces() << "\n" << "LOG: Result";
                        TRACE01 tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     TRACE01 Traces() << "\n" << "LOG: There was similar white board!";
                    //TO DO };
                };
            };
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                AddToDoNotForgetQueue(board);

                TRACE01 Traces() << "\n" << "LOG: There was situation when white player can not move!";
                TRACE01 board.printDebug();
            };
        };
    };

    return 0;
}

template <unsigned long long MQueue, unsigned long long sQueue>
bool ThreadIATreeExpander<MQueue, sQueue>::ExpandBlack(Board board, unsigned int stepNumber)
{
    TRACE01 Traces() << "\n" << "LOG: void IATreeExpander::ExpandBlack(IADecisionTree *treePointer)";

    //DEL Board board = board.GetBoard();
    unsigned short pawnNumber = board.GetNumberOfBlack();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (board.GetPreviousMurder()<12)
    {
        if (board.GetNumberOfWhite() == 0)
        {
            AddToDoNotForgetQueue(board);

            TRACE01 Traces() << "\n" << "LOG: There was situation when all White was killed!";
            TRACE01 board.printDebug();
            return 0;
        };

        unsigned short i = board.GetPreviousMurder();
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;

           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //For pons
       if (board.GetBlackPawnPons(i))
       {
           //Left Top
          if (possible.CheckHitBottomLeftBlack(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitBottomLeftBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
          //Right Top
          if (possible.CheckHitBottomRightBlack(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitBottomRightBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
       };

       if (!killFlag)
       {
           board.SetPreviousMurder(12);
           board.StartWhite();
           ExpandWhite(board);
       };

       return 0;
    };

    if (board.GetNumberOfBlack() == 0)
    {
        AddToDoNotForgetQueue(board);

        TRACE01 Traces() << "\n" << "LOG: There was situation when all Black was killed!";
        TRACE01 board.printDebug();
        return 0;
    };

    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           TRACE01 tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);

           AddToMainQueue(tempNew);

           TRACE01 Traces() << "\n" << "LOG: Result";
           TRACE01 tempNew.printDebug();
       };
       //For pons
       if (board.GetBlackPawnPons(i))
       {
           //Left Top
          if (possible.CheckHitBottomLeftBlack(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitBottomLeftBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
          //Right Top
          if (possible.CheckHitBottomRightBlack(i, board))
          {
              TRACE01 Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
              Board tempNew = board;
              TRACE01 tempNew.printDebug();
              possible.KillHitBottomRightBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);

              AddToMainQueue(tempNew);

              TRACE01 Traces() << "\n" << "LOG: Result";
              TRACE01 tempNew.printDebug();
          };
       };
    };
    //If no kills check other steps
    if (!killFlag)
    {
        TRACE01 Traces() << "\n" << "LOG:  (!killFlag) == true";
        TRACE01 Traces() << "\n" << "LOG:  pawnNumber = " << pawnNumber;
        bool canImove = false;

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {
            //Top Left
            if (possible.CheckPutTopLeftBlack(i, board))
            {
                TRACE01 Traces() << "\n" << "LOG: possible.CheckPutTopLeftBlack(" << i << ", board) == true";
                Board tempNew = board;
                TRACE01 tempNew.printDebug();
                tempNew.PutBlackTopLeftPawn(i);
                tempNew.StartWhite();
                tempNew.SetPreviousMurder(12);

                AddToMainQueue(tempNew);

                TRACE01 Traces() << "\n" << "LOG: Result";
                TRACE01 tempNew.printDebug();
                canImove = true;
            }
            //Top Right
            if (possible.CheckPutTopRightBlack(i, board))
            {
                TRACE01 Traces() << "\n" << "LOG: possible.CheckPutTopRightBlack(" << i << ", board) == true";
                Board tempNew = board;
                TRACE01 tempNew.printDebug();
                tempNew.PutBlackTopRightPawn(i);
                tempNew.StartWhite();
                tempNew.SetPreviousMurder(12);

                AddToMainQueue(tempNew);

                TRACE01 Traces() << "\n" << "LOG: Result";
                TRACE01 tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetBlackPawnPons(i))
            {
                //Bottom Left
                if (possible.CheckPutBottomLeftBlack(i, board))
                {
                    TRACE01 Traces() << "\n" << "LOG: possible.CheckPutBottomLeftBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    TRACE01 tempNew.printDebug();
                    tempNew.PutBlackBottomLeftPawn(i);

                    //TO DO if (board.IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartWhite();
                        tempNew.SetPreviousMurder(12);

                        AddToMainQueue(tempNew);

                        TRACE01 Traces() << "\n" << "LOG: Result";
                        TRACE01 tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     TRACE01 Traces() << "\n" << "LOG: There was similar Black board!";
                    //TO DO };
                };
                //Bottom Right
                if (possible.CheckPutBottomRightBlack(i, board))
                {
                    TRACE01 Traces() << "\n" << "LOG: possible.CheckPutBottomRightBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    TRACE01 tempNew.printDebug();
                    tempNew.PutBlackBottomRightPawn(i);

                    //TO DO if (board.IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartWhite();
                        tempNew.SetPreviousMurder(12);

                        AddToMainQueue(tempNew);

                        TRACE01 Traces() << "\n" << "LOG: Result";
                        TRACE01 tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     TRACE01 Traces() << "\n" << "LOG: There was similar Black board!";
                    //TO DO };
                };
            };
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                AddToDoNotForgetQueue(board);

                TRACE01 Traces() << "\n" << "LOG: There was situation when Black player can not move!";
                TRACE01 board.printDebug();
            };
        };
    };

    return 0;
}

