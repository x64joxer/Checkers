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
    #ifdef PERFORMANCE_TESTS
    {
        PerformanceTests performanceTests;
       performanceTests.Make();
    };
    #endif

    #ifdef FUNCTION_TESTS
    {
       FunctionTests functionTests;
       functionTests.Make();
    };
    #endif


    //START APP
    board = new Board();
    *board =
                std::string("| |w| |w| |w| |w|") +
                std::string("|w| |w| |w| |w| |") +
                std::string("| |w| |w| |w| |w|") +
                std::string("| | | | | | | | |") +
                std::string("| | | | | | | | |") +
                std::string("|b| |b| |b| |b| |") +
                std::string("| |b| |b| |b| |b|") +
                std::string("|b| |b| |b| |b| |");


    *board =
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | | | | | |") +
            std::string("| | | | |B| | | |") +
            std::string("| | | | | | | | |") +
            std::string("|w| | | | | | | |") +
            std::string("| | | |W| |b| |w|") +
            std::string("|b| | | | | | | |");


    checkerArea = new CheckerArea(this);
    checkerArea->SetBoard(board);

    Traces::TurnOffTraces();

    Traces() << "\n" << "Start Traces!!";
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
