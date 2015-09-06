#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define QT_NO_DEBUG_OUTPUT
#define PERFORMANCE_TESTS_OFF

#include <QMainWindow>
#include "CheckerArea.h"
#include "Board.h"
#include "Traces/Traces.h"
#include "Tests/PerformanceTests.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        CheckerArea *checkerArea;
        Board *board;

        void Init();
        void resizeEvent ( QResizeEvent * event );

};

#endif // MAINWINDOW_H
