#include "IATreeExpander.h"

IATreeExpander::IATreeExpander()
{

}

Board IATreeExpander::ExpandTheTree(IADecisionTree *treePointer)
{
    Traces() << "\n" << "LOG: void IATreeExpander::ExpandTheTree(IADecisionTree *treePointer)";
    IABoardQueue queue ;
    IADecisionTree *currentWork;
    IADecisionTree *tempWork;
    queue.ForcePushBack(treePointer);

    for (unsigned short i = 0;i<7000;i++)
    {
        currentWork = queue.PopFirst();

        if (currentWork == NULL) break;

        if (currentWork->Black())
        {            
          Traces() << "\n" << "LOG: (treePointer->Black())";          
          ExpandBlack(currentWork, queue);
        } else
        {          
          Traces() << "\n" << "LOG: (treePointer->White())";          
          ExpandWhite(currentWork, queue);          
        };        
        tempWork = currentWork;        
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

bool IATreeExpander::ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue)
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
                    queue.PushBack(treePointer->AddNextStep(tempNew,0));
                    Traces() << "\n" << "LOG: Result";
                    tempNew.printDebug();
                };
                //Top Right
                if (possible.CheckPutTopRightWhite(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutTopRightWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopRightPawn(i);
                    queue.PushBack(treePointer->AddNextStep(tempNew,0));
                    Traces() << "\n" << "LOG: Result";
                    tempNew.printDebug();
                };
            };
        };
    };

    return 0;
}

bool IATreeExpander::ExpandBlack(IADecisionTree *treePointer, IABoardQueue &queue)
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
           treePointer->SetPreviousMurder(9);
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
                    queue.PushBack(treePointer->AddNextStep(tempNew,1));
                    Traces() << "\n" << "LOG: Result";
                    tempNew.printDebug();
                };
                //Bottom Right
                if (possible.CheckPutBottomRightBlack(i, board))
                {
                    Traces() << "\n" << "LOG: possible.CheckPutBottomRightBlack(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutBlackBottomRightPawn(i);
                    queue.PushBack(treePointer->AddNextStep(tempNew,1));
                    Traces() << "\n" << "LOG: Result";
                    tempNew.printDebug();
                };
            };
        };
    };

    return 0;
}
