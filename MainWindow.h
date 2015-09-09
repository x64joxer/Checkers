#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define QT_NO_DEBUG_OUTPUT
#define PERFORMANCE_TESTS
#define FUNCTION_TESTS

#include <QMainWindow>
#include "CheckerArea.h"
#include "Board.h"
#include "Traces/Traces.h"
#include "Tests/PerformanceTests.h"
#include "Tests/FunctionTests.h"


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

private:
        Ui::MainWindow *ui;
        CheckerArea *checkerArea;
        Board *board;

        void Init();
        void resizeEvent ( QResizeEvent *);

};

#endif // MAINWINDOW_H
