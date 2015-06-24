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
    board = new Board();
    checkerArea = new CheckerArea(this);
    checkerArea->SetBoard(board);
    //board->SetWhitePawnPos(1,1,4);
    //board->SetWhitePawnPos(2,0,3);
    //board->RemovePawnFrom(2,1);
    //board->printDebug();
  //  board->SetBlackPawnPos(0,6,3);
   // board->SetWhitePawnPos(11,5,4);



   // board->SetWhitePawnPos(10,3,4);

    PawnPos temp = board->GetWhitePawnPos(9);
    qDebug() << temp.X() << " " << temp.Y();
    board->printDebug();

    IATreeExpander expander;
    IADecisionTree *tree;
    tree = new IADecisionTree();

//    tree->StartBlack();
    tree->StartWhite();
    tree->SetBoard(*board);
    expander.ExpandTheTree(tree);
    delete tree;
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
