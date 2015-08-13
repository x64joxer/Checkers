#include "CheckerArea.h"
#include "ui_CheckerArea.h"

//██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗ ██████╗ ██████╗ ███████╗
//██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██╔════╝
//██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝███████╗
//██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║   ██║██╔══██╗╚════██║
//╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║███████║
//╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝

CheckerArea::CheckerArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckerArea)
{
    ui->setupUi(this);

    board = NULL;

    field1 = QColor(0,0,0);
    field2 = QColor(255,255,255);

    pawn1 = QColor(0,0,255);
    pawn2 = QColor(255,0,0);

    cursorState = Free;
}

//███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
//██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
//█████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
//██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
//██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
//╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝

void CheckerArea::Paint()
{
    QPainter painter;
    painter.begin(this);

    PaintFields(&painter);
    PaintPawn(&painter);
    PaintGrabbedBlackPawn(&painter);

    painter.end();
}

void CheckerArea::SetBoard(Board *wsk)
{
    board = wsk;
}

void CheckerArea::PaintFields(QPainter *painter)
{
    int widthField = width() / 8;
    int heightField = height() / 8;
    bool flag = 0;

    painter->setPen(QColor(0,0,0));

    for (int y = 0;y<8;y++)
    {
        for (int x = 0;x<8;x++)
        {
            if (flag)
            {
                painter->setBrush(field1);
            } else
            {
                painter->setBrush(field2);
            };

            flag = !flag;

            painter->drawRect(x*widthField,
                              y*heightField,
                              (x*widthField)+widthField,
                              (y*heightField)+heightField);            

        };
        flag = !flag;
    };
}

void CheckerArea::PaintPawn(QPainter *painter)
{
    if (board == NULL) Traces() << "\n" << "ERROR! CheckerArea::PaintPawn(QPainter *painter) RPointer to board is empty!";
    ushort numberOfWhite = board->GetNumberOfWhite();
    ushort numberOfBlack = board->GetNumberOfBlack();
    int widthField = width() / 8;
    int heightField = height() / 8;
    PawnPos pos;

    for (int i=0;i<numberOfWhite;i++)
    {
        pos = board->GetWhitePawnPos(i);

        DrawPawn(painter,
                 (pos.X() * widthField) + (widthField /2),
                 (pos.Y() * heightField) + (heightField /2),
                 widthField,
                 heightField,1,
                 board->GetWhitePawnPons(i));

    };

    for (int i=0;i<numberOfBlack;i++)
    {
        pos = board->GetBlackPawnPos(i);

        DrawPawn(painter,
                 (pos.X() * widthField) + (widthField /2),
                 (pos.Y() * heightField) + (heightField /2),
                 widthField,
                 heightField,
                 0,
                 board->GetBlackPawnPons(i));

    };
}

void CheckerArea::PaintGrabbedBlackPawn(QPainter *painter)
{
    if (cursorState == Grab)
    {
        int widthField = width() / 8;
        int heightField = height() / 8;

        DrawPawn(painter, mouseX, mouseY, widthField, heightField, 0, board->GetBlackPawnPons(grabbed));
    };
}

void CheckerArea::DrawPawn(QPainter *painter, const int x, const int y, const int widthField, const int heightField, const bool blackWhite, const bool pons)
{
    if (blackWhite)
    {
        painter->setBrush(pawn1);
    } else
    {
        painter->setBrush(pawn2);
    };

    if (!pons)
    {

        painter->drawEllipse(QPoint(x,y),
                             widthField / 2,
                             heightField / 2);

        painter->drawEllipse(QPoint(x,y),
                             widthField / 2.7,
                             heightField / 2.7);
    } else
    {
        painter->drawEllipse(QPoint(x,y),
                             widthField / 2,
                             heightField / 2);

        painter->drawEllipse(QPoint(x,y),
                             widthField / 2.3,
                             heightField / 2.3);
    };
}

void CheckerArea::TakeMouseClickEvent(QMouseEvent *event)
{
    int widthField = width() / 8;
    int heightField = height() / 8;

    unsigned short x = (event->x() / widthField);
    unsigned short y = (event->y() / heightField);

    if (cursorState == Free)
    {
        if (board->IsBlackPawnOnPos(x,y))
        {
            grabbed = board->GetBlackPawnNumber(x,y);

            if (possibleMoves.CanIGrab(grabbed, *board))
            {
                cursorState = Grab;
            };
        };
    };
}

void CheckerArea::TakeMouseReleaseEvent(QMouseEvent *event)
{    
    int widthField = width() / 8;
    int heightField = height() / 8;

    unsigned short x = (event->x() / widthField);
    unsigned short y = (event->y() / heightField);

    if (cursorState == Grab)
    {
        Traces() << "\n" << "if (cursorState == Grab)";
        if (possibleMoves.CanIPutHere(grabbed, x, y, *board))
        {
            unsigned short killed;
            if (possibleMoves.IsKill(grabbed, x, y, *board, killed))
            {
                board->RemoveWhitePawn(killed);

                board->SetBlackPawnPos(grabbed,x,y);
                if (possibleMoves.CheckHitTopLeft(x,y,*board) | possibleMoves.CheckHitTopRight(x,y,*board))
                {
                    Traces() << "\n" << "After kill possibleMoves.CheckHitTopLeft(x,y,*board) | possibleMoves.CheckHitTopRight(x,y,*board) is true, cursorState = Free";
                    cursorState = Free;
                } else
                if (board->GetBlackPawnPons(grabbed))
                {
                    if (possibleMoves.CheckHitBottomLeft(x,y,*board) | possibleMoves.CheckHitBottomRight(x,y,*board))
                    {
                        Traces() << "\n" << "cursorState = Free";
                        cursorState = Free;
                    } //Error here
                    else
                    {
                        Traces() << "\n" << "cursorState = Free"; //In future IA !!!!!!!
                        //Test
                        IATreeExpander expander;
                        IADecisionTree *tree;
                        tree = new IADecisionTree();
                        Board copy = *board;
                        tree->StartWhite();
                        tree->SetBoard(*board);                        
                        *board =  expander.ExpandTheTree(tree);
                        delete tree;
                        Traces() << "\n" << "LOG: Before";
                        copy.printDebug();
                        Traces() << "\n" << "LOG: After";
                        board->printDebug();
                        //Test
                        cursorState = Free;
                    };
                }
                else
                {
                    Traces() << "\n" << "cursorState = Free"; //In future IA !!!!!!!
                    //Test
                    IATreeExpander expander;
                    IADecisionTree *tree;
                    tree = new IADecisionTree();
                    Board copy = *board;
                    tree->StartWhite();
                    tree->SetBoard(*board);
                    *board =  expander.ExpandTheTree(tree);
                    delete tree;
                    Traces() << "\n" << "LOG: Before";
                    copy.printDebug();
                    Traces() << "\n" << "LOG: After";
                    board->printDebug();
                    //Test
                    cursorState = Free;
                };
            } else
            {
                Traces() << "\n" << "cursorState = Free"; //In future IA !!!!!!!
                cursorState = Free;
                board->SetBlackPawnPos(grabbed,x,y);
                //Test
                IATreeExpander expander;
                IADecisionTree *tree;
                tree = new IADecisionTree();
                Board copy = *board;
                tree->StartWhite();
                tree->SetBoard(*board);
                *board =  expander.ExpandTheTree(tree);
                delete tree;
                Traces() << "\n" << "LOG: Before";
                copy.printDebug();
                Traces() << "\n" << "LOG: After";
                board->printDebug();
                //Test
            }
        } else
        {
            cursorState = Free;
            Traces() << "\n" << "cursorState = Free";
        };
    };

    repaint();
}

void CheckerArea::TakeMouseMoveEvent(QMouseEvent *event)
{
    mouseX = event->x();
    mouseY = event->y();

    if (cursorState == Grab) repaint();

}

//███████╗██╗      ██████╗ ████████╗███████╗
//██╔════╝██║     ██╔═══██╗╚══██╔══╝██╔════╝
//███████╗██║     ██║   ██║   ██║   ███████╗
//╚════██║██║     ██║   ██║   ██║   ╚════██║
//███████║███████╗╚██████╔╝   ██║   ███████║
//╚══════╝╚══════╝ ╚═════╝    ╚═╝   ╚══════╝

//███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
//██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
//█████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
//██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
//███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
//╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝

void CheckerArea::paintEvent(QPaintEvent *event)
{
    Paint();
}

void CheckerArea::mouseMoveEvent(  QMouseEvent * event)
{
    TakeMouseMoveEvent(event);
}

void CheckerArea::mousePressEvent(QMouseEvent * event)
{
    TakeMouseClickEvent(event);
}

void CheckerArea::mouseReleaseEvent(QMouseEvent *event)
{
    TakeMouseReleaseEvent(event);
}

//██████╗ ███████╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗ ██████╗ ██████╗
//██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗
//██║  ██║█████╗  ███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝
//██║  ██║██╔══╝  ╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║   ██║██╔══██╗
//██████╔╝███████╗███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║
//╚═════╝ ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝

CheckerArea::~CheckerArea()
{
    delete ui;
}
