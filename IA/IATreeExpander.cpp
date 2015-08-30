#include "IATreeExpander.h"

IATreeExpander::IATreeExpander()
{
    singleThread = true;
    numberOfSteps = 2000;
}

Board IATreeExpander::ExpandTheTreeSingleThread(IADecisionTree *treePointer)
{
    Traces() << "\n" << "LOG: void IATreeExpander::ExpandTheTreeSingleThread(IADecisionTree *treePointer)";

    IABoardQueue queue ;
    IADecisionTree *currentWork;
    IADecisionTree *tempWork;
    queue.ForcePushBack(treePointer);

    for (unsigned short i = 0;i<numberOfSteps;i++)
    {
        currentWork = queue.PopFirst();

        if (currentWork == nullptr) break;

        if (currentWork->Black())
        {
          Traces() << "\n" << "LOG: (treePointer->Black())";
          ExpandBlack(currentWork, queue, i);
        } else
        {
          Traces() << "\n" << "LOG: (treePointer->White())";
          ExpandWhite(currentWork, queue, i);
        };
        tempWork = currentWork;
        *currentPercentSteps = i / (numberOfSteps / 100);
    };

    IADecisionTree *wskTreeExpander =  queue.GetBestResult();

    if (wskTreeExpander)
    {
        Board temp = /*currentWork*/tempWork->GetOldestAncestor(queue.GetBestResult());

        return temp;
    };

    //No possible moves
    Traces() << "\n" << "LOG: IATreeExpander::ExpandTheTree(IADecisionTree *treePointer) No possible moves!!";
    return  treePointer->GetBoard();
}

Board IATreeExpander::ExpandTheTreeMultiThread(IADecisionTree *treePointer)
{

}

void IATreeExpander::Move(Board * boardRef, std::atomic_bool * flag, std::atomic<int> *percentSteps)
{
    IATreeExpander expander;
    IADecisionTree *tree;
    tree = new IADecisionTree();
    Board copy = *boardRef;
    tree->StartWhite();
    tree->SetPreviousMurder(12);
    tree->SetBoard(*boardRef);    
    Traces() << "\n" << "LOG: After";
    boardRef->printDebug();
    *boardRef =  expander.ExpandTheTree(tree, percentSteps);
    *flag = true;
    delete tree;
}

Board IATreeExpander::ExpandTheTree(IADecisionTree *treePointer, std::atomic<int> *percentSteps)
{
    Traces() << "\n" << "LOG: void IATreeExpander::ExpandTheTree(IADecisionTree *treePointer)";    

    Board tempBoard;
    currentPercentSteps = percentSteps;


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if (singleThread)
    {
        tempBoard =  ExpandTheTreeSingleThread(treePointer);
    } else
    {
        tempBoard = ExpandTheTreeMultiThread(treePointer);
    };

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;

    return tempBoard;        
}

bool IATreeExpander::ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber)
{
    Traces() << "\n" << "LOG: void IATreeExpander::ExpandWhite(IADecisionTree *treePointer)";

    Board board = treePointer->GetBoard();
    unsigned short pawnNumber = board.GetNumberOfWhite();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (treePointer->GetPreviousMurder()<12)
    {
        unsigned short i = treePointer->GetPreviousMurder();
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
       };

       if (!killFlag)
       {
           treePointer->SetPreviousMurder(12);
           treePointer->StartBlack();
           ExpandBlack(treePointer, queue);
       };

       return 0;
    };
    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();           
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
       };
    };    
    //If no kills check other steps
    if (!killFlag)
    {
        Traces() << "\n" << "LOG:  (!killFlag) == true";
        bool canImove = false;

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {            
            //Bottom Left
            if (possible.CheckPutBottomLeftWhite(i, board))
            {
                Traces() << "\n" << "LOG: possible.CheckPutBottomLeftWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomLeftPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,0));
                Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //Bottom Right
            if (possible.CheckPutBottomRightWhite(i, board))
            {
                Traces() << "\n" << "LOG: possible.CheckPutBottomRightWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomRightPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,0));
                Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetWhitePawnPons(i))
            {
                //Top Left
                if (possible.CheckPutTopLeftWhite(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutTopLeftWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopLeftPawn(i);

                    if (treePointer->IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    {
                        queue.PushBack(treePointer->AddNextStep(tempNew,0));
                        Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    } else
                    {
                        Traces() << "\n" << "LOG: There was similar white board!";
                    };
                };
                //Top Right
                if (possible.CheckPutTopRightWhite(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutTopRightWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopRightPawn(i);

                    if (treePointer->IsSimilarWhiteInPatch(treePointer,tempNew) == false)
                    {
                        queue.PushBack(treePointer->AddNextStep(tempNew,0));
                        Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    } else
                    {
                        Traces() << "\n" << "LOG: There was similar white board!";
                    };
                };
            };            
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                queue.PushBackDoNotForget(treePointer);
                Traces() << "\n" << "LOG: There was situation when white player can not move!";
                treePointer->GetBoard().printDebug();
            };
        };
    };

    return 0;
}

bool IATreeExpander::ExpandBlack(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber)
{
    Traces() << "\n" << "LOG: void IATreeExpander::ExpandBlack(IADecisionTree *treePointer)";

    Board board = treePointer->GetBoard();
    unsigned short pawnNumber = board.GetNumberOfBlack();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (treePointer->GetPreviousMurder()<9)
    {
        unsigned short i = treePointer->GetPreviousMurder();
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };

       //For pons
       if (board.GetBlackPawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitBottomLeftBlack(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomLeftBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomLeftBlack(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitBottomRightBlack(i, board))
          {
              Traces() << "\n" << "LOG: possible.CheckHitBottomRightBlack(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitBottomRightBlack(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
              Traces() << "\n" << "LOG: Result";
              tempNew.printDebug();
          };

       };

       if (!killFlag)
       {
           treePointer->SetPreviousMurder(12);
           treePointer->StartWhite();
           ExpandWhite(treePointer, queue);
       };

       return 0;
    };
    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Top
       if (possible.CheckHitTopLeftBlack(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomLeftBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopLeftBlack(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Top
       if (possible.CheckHitTopRightBlack(i, board))
       {
           Traces() << "\n" << "LOG: possible.CheckHitBottomRightBlack(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitTopRightBlack(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
           Traces() << "\n" << "LOG: Result";
           tempNew.printDebug();
       };

       //For pons
       if (board.GetBlackPawnPons(i))
       {
          //Left Bottom
         if (possible.CheckHitBottomLeftBlack(i, board))
         {
             Traces() << "\n" << "LOG: possible.CheckHitBottomLeftBlack(" << i << ", board) == true";
             Board tempNew = board;
             tempNew.printDebug();
             possible.KillHitBottomLeftBlack(i, tempNew);
             killFlag = true;
             queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
             Traces() << "\n" << "LOG: Result";
             tempNew.printDebug();
         };
         //Right Bottom
         if (possible.CheckHitBottomRightBlack(i, board))
         {
             Traces() << "\n" << "LOG: possible.CheckHitBottomRightBlack(" << i << ", board) == true";
             Board tempNew = board;
             tempNew.printDebug();
             possible.KillHitBottomRightBlack(i, tempNew);
             killFlag = true;
             queue.PushBack(treePointer->AddNextStep(tempNew,0,i));
             Traces() << "\n" << "LOG: Result";
             tempNew.printDebug();
         };
       };
    };
    //If no kills check other steps
    if (!killFlag)
    {
        Traces() << "\n" << "LOG:  (!killFlag) == true";
        bool canImove = false;
        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {                        
            //Top Left
            if (possible.CheckPutTopLeftBlack(i, board))
            {
                Traces() << "\n" << "LOG: possible.CheckPutTopLeftBlack(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutBlackTopLeftPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,1));
                Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //Top Right
            if (possible.CheckPutTopRightBlack(i, board))
            {
                Traces() << "\n" << "LOG: possible.CheckPutTopRightBlack(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutBlackTopRightPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,1));
                Traces() << "\n" << "LOG: Result";
                tempNew.printDebug();
                canImove = true;
            };
            //For pons
            if (board.GetBlackPawnPons(i))
            {
                //Bottom Left
                if (possible.CheckPutBottomLeftBlack(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutBottomLeftBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutBlackBottomLeftPawn(i);
                    if (treePointer->IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    {
                        queue.PushBack(treePointer->AddNextStep(tempNew,1));
                        Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    } else
                    {
                        Traces() << "\n" << "LOG: There was similar board!";
                    };
                };
                //Bottom Right
                if (possible.CheckPutBottomRightBlack(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutBottomRightBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutBlackBottomRightPawn(i);

                    if (treePointer->IsSimilarBlackInPatch(treePointer,tempNew) == false)
                    {
                        queue.PushBack(treePointer->AddNextStep(tempNew,1));
                        Traces() << "\n" << "LOG: Result";
                        tempNew.printDebug();
                        canImove = true;
                    } else
                    {
                        Traces() << "\n" << "LOG: There was similar board!";
                    };
                };
            };            
        };
        if (!canImove)
        {
            if (stepNumber>0)
            {
                queue.PushBackDoNotForget(treePointer);
                Traces() << "\n" << "LOG: There was situation when black player can not move!";
                treePointer->GetBoard().printDebug();
            };
        };
    };

    return 0;
}
