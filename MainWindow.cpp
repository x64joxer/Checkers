#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (ProgramVariables::IsWorker())
    {
        Traces::SetTraceFolder("trace");
        Traces::TurnOnTraces();
        workerTCP = new WorkerTCP(this);
        workerTCP->ConnectToServer("192.168.0.4",6000);
    } else
    {
        Init();
    };
}


void MainWindow::Init()
{
    Traces::SetTraceFolder("trace");

    FillThreadsListMenu();

    connect(ui->menuNumber_of_threads,SIGNAL(triggered(QAction*)),this,SLOT(SetNumOfThreads(QAction*)));

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

    checkerArea = new CheckerArea(this);
    checkerArea->SetBoard(board);

    server = new ServerTCP(this);
    Traces::TurnOnTraces();

    server->StartLisning(QHostAddress::Any,6000);


}

void MainWindow::FillThreadsListMenu()
{
    ui->menuNumber_of_threads->clear();

    for (int i=1;i<=ProgramVariables::GetMaxNumberOfThreads();i++)
    {
        if (i!=ProgramVariables::GetNumberOfThreads())
        {
            ui->menuNumber_of_threads->addAction(QString::number(i));
        } else
        {
            ui->menuNumber_of_threads->addAction(QString::number(i) + " <<");
        };
    }
}

void MainWindow::resizeEvent( QResizeEvent *)
{
    checkerArea->move(0,30);
    checkerArea->resize(width(),height()-30);
}

void MainWindow::SetNumOfThreads(QAction* action)
{
    QString act = action->text().remove('&');
            act = act.remove('>');
            act = act.remove('<');


    ProgramVariables::SetNumberOfThreads(act.toInt());
    FillThreadsListMenu();
}

void MainWindow::on_actionTraces_triggered()
{
    if (Traces::GetTraceFlag())
    {
        Traces::TurnOffTraces();
    } else
    {
        Traces::TurnOnTraces();
    };
}

MainWindow::~MainWindow()
{
    delete checkerArea;
    delete board;
    delete server;
    delete workerTCP;
    delete ui;
}
