#include "ThreadIA/ThreadIATreeExpander.h"

template <unsigned long int MQueue, unsigned long int sQueue>
ThreadIATreeExpander<MQueue, sQueue>::ThreadIATreeExpander()
    : trace(true),
    queueSize(MQueue),
    lastQueueElement(0),
    firstQueueElement(0),    

    doNotForgetQueueSize(sQueue/50),
    lastDoNotForgetQueueElement(0)

{

}

template <unsigned long int MQueue, unsigned long int sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::Expand(unsigned int howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue)
{
    if (trace) { Traces() << "\n" << "LOG: void ThreadIATreeExpander<MQueue, sQueue>::Expand(unsigned int howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue)"; };

    queue[0] = mainBoardQueue.PopFront();
    unsigned int step = 0;
    unsigned long current;
    bool finish = false;

    while (step < howManySteps)
    {
        for (current = firstQueueElement; current <= lastQueueElement; )
        {            

            //Expand current element
            if (queue[current].Black())
            {
              if (trace) { Traces() << "\n" << "LOG: (treePointer->Black())"; };
              firstQueueElement = current+1;
              ExpandBlack(queue[current], step);              
              //lastQueueElement = firstQueueElement;
            } else
            {
              if (trace) { Traces() << "\n" << "LOG: (treePointer->White())"; };
              firstQueueElement = current+1;
              ExpandWhite(queue[current], step);
              //lastQueueElement = firstQueueElement;
            };

            if (trace) { Traces() << "\n" << "LOG: step++"; };
            step++;

            //Finish job
            if (step >= howManySteps) break;

            //Check if time to transfer data
            if (lastQueueElement>=firstQueueElement)
            {
                if (frequencyOfTransferData<=lastQueueElement-firstQueueElement)
                {

                    if (trace)  Traces() << "\n" << "LOG:" << firstQueueElement;
                        if (trace)  Traces() << "\n" << "LOG:" << lastQueueElement;
                        TransferBoards(mainBoardQueue);
                        queue[0] = mainBoardQueue.PopFront();
                        current = 0;
                        continue;
                };
            };

            ++current;

            if (trace)  Traces() << "\n" << "LOG:" << firstQueueElement;
            if (trace)  Traces() << "\n" << "LOG:" << lastQueueElement;
            if (trace)  Traces() << "\n" << "LOG:" << current;
        };

        if (trace) { Traces() << "\n" << "LOG: for (current = firstQueueElement; current <= lastQueueElement; ) END";};

        if (trace)  Traces() << "\n" << "LOG:" << firstQueueElement;
            if (trace)  Traces() << "\n" << "LOG:" << lastQueueElement;

        //Finish job
        if (step >= howManySteps)
        {
            if (trace) { Traces() << "\n" << "LOG: (step >= howManySteps) finihing job!"; };
            break;
        };

        //No jobs take more from global queue
        if (step < howManySteps)
        {
            if (trace) { Traces() << "\n" << "LOG: No jobs. Taking fom global queue"; };

            TransferBoards(mainBoardQueue);
            queue[0] = mainBoardQueue.PopFront();

            if (queue[0].GetNullBoard())
            {
                if (trace) { Traces() << "\n" << "LOG: No job in global queue. Finishing thread."; };
                break;
            };

            lastQueueElement =0;
            firstQueueElement =0;
        }

        //New begining
        //firstQueueElement = current;
    };

    if (trace) { Traces() << "\n" << "LOG: Number of temporary queue array " << lastQueueElement; };    
    TransferBoards(mainBoardQueue);
}

template <unsigned long int MQueue, unsigned long int sQueue>
void ThreadIATreeExpander<MQueue, sQueue>::TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue)
{
    if (trace) { Traces() << "\n" << "ThreadIATreeExpander<MQueue, sQueue>::TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue)";};

    if (lastQueueElement>=firstQueueElement)
    {
        if ((lastQueueElement-firstQueueElement)+1>0)
        {
            for (unsigned long i=firstQueueElement;i<=lastQueueElement;i++)
            {
                if (trace)  Traces() << "\n" << "LOG: mainBoardQueue.PushBack(queue[i])";
                mainBoardQueue.PushBack(queue[i]);
            };

            firstQueueElement =0;
            lastQueueElement=0;
        };
    };

    if (lastDoNotForgetQueueElement>0)
    {
        for (unsigned long i=1;i<=lastDoNotForgetQueueElement;i++)
        {
            mainBoardQueue.PushBackDoNotForget(queue[i]);
        };
       lastDoNotForgetQueueElement = 0;
    };

}

template <unsigned long int MQueue, unsigned long int sQueue>
bool ThreadIATreeExpander<MQueue, sQueue>::ExpandWhite(Board board, unsigned int stepNumber)
{
    if (trace) { Traces() << "\n" << "LOG: void IATreeExpander::ExpandWhite(IADecisionTree *treePointer)";};

    //DEL Board board = board.GetBoard();
    unsigned short pawnNumber = board.GetNumberOfWhite();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (board.GetPreviousMurder()<12)
    {
        if (board.GetNumberOfBlack() == 0)
        {
            if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)
            {
                if (trace) { Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue"; };
            };
            doNotForgetQueue[lastDoNotForgetQueueElement] = board;

            if (trace) { Traces() << "\n" << "LOG: There was situation when all black was killed!"; };
            board.printDebug();
            return 0;
        };

        unsigned short i = board.GetPreviousMurder();
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           if (trace) { Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true"; };
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;

           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;

           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
       };

       if (!killFlag)
       {
           board.SetPreviousMurder(12);
           board.StartBlack();
           ExpandBlack(board);
       };

       return 0;
    };

    if (board.GetNumberOfWhite() == 0)
    {
        if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)
        {
            if (trace) Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
        };
        doNotForgetQueue[lastDoNotForgetQueueElement] = board;

        if (trace) Traces() << "\n" << "LOG: There was situation when all white was killed!";
        board.printDebug();
        return 0;
    };

    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           tempNew.StartWhite();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              tempNew.StartWhite();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
       };
    };
    //If no kills check other steps
    if (!killFlag)
    {
        if (trace) Traces() << "\n" << "LOG:  (!killFlag) == true";
        bool canImove = false;

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {
            //Bottom Left
            if (possible.CheckPutBottomLeftWhite(i, board))
            {
                if (trace) Traces() << "\n" << "LOG: possible.CheckPutBottomLeftWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomLeftPawn(i);
                tempNew.StartBlack();
                tempNew.SetPreviousMurder(12);
                if (++lastQueueElement > queueSize-1)
                {
                    if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                };
                queue[lastQueueElement] = tempNew;
                if (trace) Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //Bottom Right
            if (possible.CheckPutBottomRightWhite(i, board))
            {
                if (trace) Traces() << "\n" << "LOG: possible.CheckPutBottomRightWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomRightPawn(i);
                tempNew.StartBlack();
                tempNew.SetPreviousMurder(12);
                if (++lastQueueElement > queueSize-1)
                {
                    if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                };
                queue[lastQueueElement] = tempNew;
                if (trace) Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetWhitePawnPons(i))
            {
                //Top Left
                if (possible.CheckPutTopLeftWhite(i, board))
                {
                    if (trace) Traces() << "\n" << "LOG: possible.CheckPutTopLeftWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopLeftPawn(i);

                    //TO DO if (board.IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartBlack();
                        tempNew.SetPreviousMurder(12);
                        if (++lastQueueElement > queueSize-1)
                        {
                            if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                        };
                        queue[lastQueueElement] = tempNew;
                        if (trace) Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     if (trace) Traces() << "\n" << "LOG: There was similar white board!";
                    //TO DO };
                };
                //Top Right
                if (possible.CheckPutTopRightWhite(i, board))
                {
                    if (trace) Traces() << "\n" << "LOG: possible.CheckPutTopRightWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopRightPawn(i);

                    //TO DO if (board.IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartBlack();
                        tempNew.SetPreviousMurder(12);
                        if (++lastQueueElement > queueSize-1)
                        {
                            if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                        };
                        queue[lastQueueElement] = tempNew;
                        if (trace) Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     if (trace) Traces() << "\n" << "LOG: There was similar white board!";
                    //TO DO };
                };
            };
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
                doNotForgetQueue[lastDoNotForgetQueueElement] = board;

                if (trace) Traces() << "\n" << "LOG: There was situation when white player can not move!";
                board.printDebug();
            };
        };
    };

    return 0;
}

template <unsigned long int MQueue, unsigned long int sQueue>
bool ThreadIATreeExpander<MQueue, sQueue>::ExpandBlack(Board board, unsigned int stepNumber)
{
    if (trace) Traces() << "\n" << "LOG: void IATreeExpander::ExpandBlack(IADecisionTree *treePointer)";

    //DEL Board board = board.GetBoard();
    unsigned short pawnNumber = board.GetNumberOfBlack();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (board.GetPreviousMurder()<12)
    {
        if (board.GetNumberOfWhite() == 0)
        {
            if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)
            {
                if (trace) Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
            };
            doNotForgetQueue[lastDoNotForgetQueueElement] = board;

            if (trace) Traces() << "\n" << "LOG: There was situation when all White was killed!";
            board.printDebug();
            return 0;
        };

        unsigned short i = board.GetPreviousMurder();
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;

           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;

           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetBlackPawnPons(i))
       {
           //Left Top
          if (possible.CheckHitBottomLeftBlack(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomLeftBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Top
          if (possible.CheckHitBottomRightBlack(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomRightBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
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
        if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
        doNotForgetQueue[lastDoNotForgetQueueElement] = board;

        if (trace) Traces() << "\n" << "LOG: There was situation when all Black was killed!";
        board.printDebug();
        return 0;
    };

    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           tempNew.StartBlack();
           tempNew.SetPreviousMurder(i);
           if (++lastQueueElement > queueSize-1)
           {
               if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
           };
           queue[lastQueueElement] = tempNew;
           if (trace) Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetBlackPawnPons(i))
       {
           //Left Top
          if (possible.CheckHitBottomLeftBlack(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopLeftBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomLeftBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Top
          if (possible.CheckHitBottomRightBlack(i, board))
          {
              if (trace) Traces() << "\n" << "LOG: possible.CheckHitTopRightBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomRightBlack(i, tempNew);
              killFlag = true;
              tempNew.StartBlack();
              tempNew.SetPreviousMurder(i);
              if (++lastQueueElement > queueSize-1)
              {
                  if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
              };
              queue[lastQueueElement] = tempNew;
              if (trace) Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
       };
    };
    //If no kills check other steps
    if (!killFlag)
    {
        if (trace) Traces() << "\n" << "LOG:  (!killFlag) == true";
        if (trace) Traces() << "\n" << "LOG:  pawnNumber = " << pawnNumber;
        bool canImove = false;

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {
            //Top Left
            if (possible.CheckPutTopLeftBlack(i, board))
            {
                if (trace) Traces() << "\n" << "LOG: possible.CheckPutTopLeftBlack(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutBlackTopLeftPawn(i);
                tempNew.StartWhite();
                tempNew.SetPreviousMurder(12);
                if (++lastQueueElement > queueSize-1)
                {
                    if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                };
                queue[lastQueueElement] = tempNew;
                if (trace) Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            }
            //Top Right
            if (possible.CheckPutTopRightBlack(i, board))
            {
                if (trace) Traces() << "\n" << "LOG: possible.CheckPutTopRightBlack(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutBlackTopRightPawn(i);
                tempNew.StartWhite();
                tempNew.SetPreviousMurder(12);
                if (++lastQueueElement > queueSize-1)
                {
                    if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                };
                queue[lastQueueElement] = tempNew;
                if (trace) Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetBlackPawnPons(i))
            {
                //Bottom Left
                if (possible.CheckPutBottomLeftBlack(i, board))
                {
                    if (trace) Traces() << "\n" << "LOG: possible.CheckPutBottomLeftBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutBlackBottomLeftPawn(i);

                    //TO DO if (board.IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartWhite();
                        tempNew.SetPreviousMurder(12);
                        if (++lastQueueElement > queueSize-1)
                        {
                            if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                        };
                        queue[lastQueueElement] = tempNew;
                        if (trace) Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     if (trace) Traces() << "\n" << "LOG: There was similar Black board!";
                    //TO DO };
                };
                //Bottom Right
                if (possible.CheckPutBottomRightBlack(i, board))
                {
                    if (trace) Traces() << "\n" << "LOG: possible.CheckPutBottomRightBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutBlackBottomRightPawn(i);

                    //TO DO if (board.IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    //TO DO {
                        tempNew.StartWhite();
                        tempNew.SetPreviousMurder(12);
                        if (++lastQueueElement > queueSize-1)
                        {
                            if (trace) Traces() << "\n" << "ERROR: No free memory cells in main queue";
                        };
                        queue[lastQueueElement] = tempNew;
                        if (trace) Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    //TO DO } else
                    //TO DO {
                    //TO DO     if (trace) Traces() << "\n" << "LOG: There was similar Black board!";
                    //TO DO };
                };
            };
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                if (++lastDoNotForgetQueueElement > doNotForgetQueueSize-1)
                {
                    if (trace) Traces() << "\n" << "ERROR: No free memory cells in main do not forget queue";
                };
                doNotForgetQueue[lastDoNotForgetQueueElement] = board;

                if (trace) Traces() << "\n" << "LOG: There was situation when Black player can not move!";
                board.printDebug();
            };
        };
    };

    return 0;
}
