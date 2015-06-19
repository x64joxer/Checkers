#include "IATreeExpander.h"

IATreeExpander::IATreeExpander()
{

}

void IATreeExpander::ExpandTheTree(IADecisionTree *treePointer)
{
    qDebug() << "LOG: void IATreeExpander::ExpandTheTree(IADecisionTree *treePointer)";
    IABoardQueue queue ;

    if (treePointer->Black())
    {
      qDebug() << "LOG: (treePointer->Black())";
    } else
    {
      qDebug() << "LOG: (treePointer->White())";
      ExpandWhite(treePointer, queue);
    };
}

bool IATreeExpander::ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue)
{
    qDebug() << "LOG: void IATreeExpander::ExpandWhite(IADecisionTree *treePointer)";

    Board board = treePointer->GetBoard();
    unsigned short pawnNumber = board.GetNumberOfWhite();
    IAPossibleMoves possible;
    bool killFlag = false;

    if (treePointer->GetPreviousMurder()<9)
    {
        unsigned short i = treePointer->GetPreviousMurder();
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           qDebug() << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           qDebug() << "LOG: Result";
           tempNew.printDebug();
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           qDebug() << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           qDebug() << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              qDebug() << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              qDebug() << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              qDebug() << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              qDebug() << "LOG: Result";
              tempNew.printDebug();
          };
       };

       if (!killFlag)
       {
           //ExpandBlack(treePointer);
       };

       return 0;
    };
    //Check possible kills
    for (unsigned short i=0;i<pawnNumber;i++)
    {
        //Left Bottom
       if (possible.CheckHitBottomLeftWhite(i, board))
       {
           qDebug() << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomLeftWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           qDebug() << "LOG: Result";
           tempNew.printDebug();           
       };
       //Right Bottom
       if (possible.CheckHitBottomRightWhite(i, board))
       {
           qDebug() << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
           Board tempNew = board;
           tempNew.printDebug();
           possible.KillHitBottomRightWhite(i, tempNew);
           killFlag = true;
           queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
           qDebug() << "LOG: Result";
           tempNew.printDebug();
       };
       //For pons
       if (board.GetWhitePawnPons(i))
       {
           //Left Bottom
          if (possible.CheckHitTopLeftWhite(i, board))
          {
              qDebug() << "LOG: possible.CheckHitBottomLeftWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopLeftWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              qDebug() << "LOG: Result";
              tempNew.printDebug();
          };
          //Right Bottom
          if (possible.CheckHitTopRightWhite(i, board))
          {
              qDebug() << "LOG: possible.CheckHitBottomRightWhite(" << i << ", board) == true";
              Board tempNew = board;
              tempNew.printDebug();
              possible.KillHitTopRightWhite(i, tempNew);
              killFlag = true;
              queue.PushBack(treePointer->AddNextStep(tempNew,1,i));
              qDebug() << "LOG: Result";
              tempNew.printDebug();
          };
       };
    };    
    //If no kills check other steps
    if (!killFlag)
    {
        qDebug() << "LOG:  (!killFlag) == true";

        //Check possible puts
        for (unsigned short i=0;i<pawnNumber;i++)
        {
            //Bottom Left
            if (possible.CheckPutBottomLeftWhite(i, board))
            {
                qDebug() << "LOG: possible.CheckPutBottomLeftWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomLeftPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,0));
                qDebug() << "LOG: Result";
                tempNew.printDebug();
            };
            //Bottom Right
            if (possible.CheckPutBottomRightWhite(i, board))
            {
                qDebug() << "LOG: possible.CheckPutBottomRightWhite(" << i << ", board) == true";
                Board tempNew = board;
                tempNew.printDebug();
                tempNew.PutWhiteBottomRightPawn(i);
                queue.PushBack(treePointer->AddNextStep(tempNew,0));
                qDebug() << "LOG: Result";
                tempNew.printDebug();
            };
            //For pons
            if (board.GetWhitePawnPons(i))
            {
                //Top Left
                if (possible.CheckPutTopLeftWhite(i, board))
                {
                    qDebug() << "LOG: possible.CheckPutTopLeftWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopLeftPawn(i);
                    queue.PushBack(treePointer->AddNextStep(tempNew,0));
                    qDebug() << "LOG: Result";
                    tempNew.printDebug();
                };
                //Top Right
                if (possible.CheckPutTopRightWhite(i, board))
                {
                    qDebug() << "LOG: possible.CheckPutTopRightWhite(" << i << ", board) == true";
                    Board tempNew = board;
                    tempNew.printDebug();
                    tempNew.PutWhiteTopRightPawn(i);
                    queue.PushBack(treePointer->AddNextStep(tempNew,0));
                    qDebug() << "LOG: Result";
                    tempNew.printDebug();
                };
            };
        };
    };

    return 0;
}
