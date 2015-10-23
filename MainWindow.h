#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define QT_NO_DEBUG_OUTPUT
#define PERFORMANCE_TESTS_OFF
#define FUNCTION_TESTS_OFF

#include <QMainWindow>
#include "CheckerArea.h"
#include "Board.h"
#include "Traces/Traces.h"
#include "Tests/PerformanceTests.h"
#include "Tests/FunctionTests.h"
#include "TCP/ServerTCP.h"
#include "TCP/WorkerTCP.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private slots:
    void on_actionTraces_triggered();
    void SetNumOfThreads(QAction* action);

private:
        Ui::MainWindow *ui;
        CheckerArea *checkerArea;
        Board *board;
        ServerTCP *server;
        WorkerTCP *workerTCP;

        void Init();
        void FillThreadsListMenu();
        void resizeEvent ( QResizeEvent *);

};

#endif // MAINWINDOW_H
