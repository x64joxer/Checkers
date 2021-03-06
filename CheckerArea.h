#ifndef CHECKERAREA_H
#define CHECKERAREA_H

#include <QDir>
#include <QGraphicsEllipseItem>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <thread>
#include <atomic>
#include "Board.h"
#include "PossibleMoves.h"
#include "ThreadIA/ThreadIAMove.h"
#include "ThreadIA/ThreadIAMove.cpp"
#include "ProgramVariables.h"
#include "TCP/MessageHandler.h"

namespace Ui {
class CheckerArea;
}

class CheckerArea : public QWidget
{
        Q_OBJECT

    public:
        explicit CheckerArea(QWidget *parent = 0);
        void SetBoard(Board *wsk);
        void SetMessageHandler(MessageHandler *wsk);
        ~CheckerArea();

    private:
        Ui::CheckerArea *ui;
        QColor field1;
        QColor field2;
        QColor pawn1;
        QColor pawn2;

        Board *board;
        Board previousBoard;
        unsigned short int displayedBoard;

        PossibleMoves possibleMoves;

        enum CursorState
        { Free, Grab, WaitForIA } cursorState;
        int mouseX;
        int mouseY;
        unsigned short grabbed;

        std::thread iaJob;
        std::atomic_bool endIaJobFlag;
        std::atomic<int> currentPercentOfSteps;
        ThreadIAMove<3000000> jobExpander2;
        MessageHandler * messageHandler;

        QTimer *waitForIATimer;

        void Paint();
        void PaintFields(QPainter *painter);
        void PaintPawn(QPainter *painter);
        void PaintGrabbedBlackPawn(QPainter *painter);
        void PaintPercentageEllipse(QPainter *painter);
        void DrawPawn(QPainter *painter, const int x, const int y, const int widthField, const int heightField, const bool blackWhite, const bool pons);

        void StartThinking();

        void TakeMouseClickEvent(QMouseEvent *event);
        void TakeMouseReleaseEvent(QMouseEvent *event);
        void TakeMouseMoveEvent(QMouseEvent *event);
        void TakeKeyPressed(QKeyEvent *event);

        void paintEvent(QPaintEvent *);
        void mouseMoveEvent(  QMouseEvent * event);
        void mousePressEvent(QMouseEvent * event);
        void mouseReleaseEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);

    private slots:
        void CheckStatus();
};

#endif // CHECKERAREA_H
