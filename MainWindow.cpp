#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}


void MainWindow::Init()
{
    {
        PerformanceTests performanceTests;
        performanceTests.Make();
    };

    board = new Board();
    checkerArea = new CheckerArea(this);

   /* *board =
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | |W| |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | |b| |") +
            std::string("| |b| |b| | | |b|") +
            std::string("| | | | | | | | |");*/

    //board->RemoveWhitePawn(10);
    //Traces::TurnOnTraces();
    //Traces() << board->GetNumberOfWhite();
    //Traces() << board->GetNumberOfBlack();
    //board->RemoveBlackPawn(2);

    checkerArea->SetBoard(board);

  // Traces::TurnOnTraces();
   /* ThreadIAMove<900000> move;
    move.operator ()(board);*/

    Traces() << "\n" << "Start Traces!!";

    //board->SetWhitePawnPos(1,1,4);
    //board->SetWhitePawnPos(2,0,3);
    //board->RemovePawnFrom(2,1);
    //board->printDebug();
  //  board->SetBlackPawnPos(0,6,3);
   // board->SetWhitePawnPos(11,5,4);



   // board->SetWhitePawnPos(10,3,4);

    //PawnPos temp = board->GetWhitePawnPos(9);
    //Traces() << "\n" << temp.X() << " " << temp.Y();
    //board->printDebug();

   // IATreeExpander expander;
  //  IADecisionTree *tree;
   // tree = new IADecisionTree();

//    tree->StartBlack();
 //   tree->StartWhite();
  //  tree->SetBoard(*board);
  //  expander.ExpandTheTree(tree);
   // delete tree;

    //Tests

    /*Board board1;
    board1 =
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | |w|") +
            std::string("| | | | | | | |w|") +
            std::string("| | | | |b| | | |") +
            std::string("| | | | | |b| |b|") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |");

    Board board2;
     board2 =
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | |w|") +
            std::string("| | | | | | | |w|") +
            std::string("| | | | |b| | | |") +
            std::string("| | | | | |b| |b|") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |");

    if (board1 == board2)
    {
        Traces() << "\n(board1 == board2)";
    } else
    {
        Traces() << "(board1 != board2)";
    };


    {
        Board *board1 = new Board();
        Board *boardtest = new Board();
        Board *boardnext[20];
        IADecisionTree *treenext[20];

        *board1 =
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | |w|") +
                std::string("| | | | | | | |w|") +
                std::string("| | | | |b| | | |") +
                std::string("| | | | | |b| |B|") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |");

        *boardtest =
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | |w|") +
                std::string("| | | | | | | |w|") +
                std::string("| | | | |b| | | |") +
                std::string("| | | | | |b| |B|") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |");



        IADecisionTree *tree1;
        tree1 = new IADecisionTree();
        tree1->StartBlack();
        tree1->SetBoard(*board1);
        tree1->SetPreviousElement(nullptr);

        int howmuch = 13;

        for (int i=0;i<howmuch;i++)
        {
            boardnext[i] = new Board();
            *boardnext[i] =  std::string("| | | | | | | | |") +
                    std::string("| | | | | | | |w|") +
                    std::string("| | | | | | | |w|") +
                    std::string("| | | | |b| | | |") +
                    std::string("| | | | | | | | |") +
                    std::string("| | | | | | | | |") +
                    std::string("| | | | | | | | |") +
                    std::string("| | | | | | | | |");


        };

        treenext[0] = new IADecisionTree();
        treenext[0]->StartWhite();
        treenext[0]->SetBoard(*boardnext[0]);
        treenext[0]->SetPreviousElement(tree1);

        for (int i=1;i<howmuch;i++)
        {

            treenext[i] = new IADecisionTree();
            treenext[i]->StartWhite();
            treenext[i]->SetBoard(*boardnext[i]);
            treenext[i]->SetPreviousElement(treenext[i-1]);
        };


        if (treenext[0]->IsSimilarBlackInPatch(treenext[howmuch-1],*boardtest))
        {
            Traces() << "tree3->IsSimilarBlackInPatch(tree3,*board3) = true";
        } else
        {
            Traces() << "tree3->IsSimilarBlackInPatch(tree3,*board3) = false";
        };

    }*/

    /*std::stringstream ss;
    ss << std::this_thread::get_id();
    uint64_t id = std::stoull(ss.str());
    qDebug() << id;

    std::stringstream ss2;
    ss2 << std::this_thread::get_id();
    uint64_t id2 = std::stoull(ss.str());
    qDebug() << id2;
    qDebug() << "dfdf"; */

    //Traces::TurnOnTraces();

   /* board->StartBlack();
    ThreadIABoardQueue<90000> queuetest;
    queuetest.PushBack(*board);
    ThreadIATreeExpander<90000,5000> expander;

    expander.Expand(4000,3000,queuetest);


    Board example;
    Board example2;
            example2 =  std::string("| | | | | | | | |") +
                               std::string("| | | | | | | |w|") +
                               std::string("| | | | | | | |w|") +
                               std::string("| | | | |b| | | |") +
                               std::string("| | | | | | | | |") +
                               std::string("| | | | | | | | |") +
                               std::string("| | | | | | | | |") +
                               std::string("| | | | | | | | |");
            example2.printDebug();*/



    //5 elements
   /* queuetest.PushBack(example);
    queuetest.PushBack(example);
    queuetest.PushBack(example);
    queuetest.PushBack(example);
    queuetest.PushBack(example);

    //Take first
    queuetest.PopFront();
    queuetest.PopFront();

    queuetest.PushBack(example);
    queuetest.PushBack(example2);

    queuetest.PopFront();
    queuetest.PopFront();
    queuetest.PopFront();
    queuetest.PopFront();
    example = queuetest.PopFront();

    example.printDebug();*/


}

void MainWindow::resizeEvent( QResizeEvent * event )
{
    checkerArea->move(0,30);
    checkerArea->resize(width(),height()-30);
}

MainWindow::~MainWindow()
{
    delete checkerArea;
    delete board;
    delete ui;
}
