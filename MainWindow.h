#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CheckerArea.h"
#include "Board.h"
#include "IA/IADecisionTree.h"
#include "IA/IATreeExpander.h"

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
