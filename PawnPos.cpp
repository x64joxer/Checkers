#include "PawnPos.h"

PawnPos::PawnPos()
{

}

PawnPos::PawnPos(const int X, const int Y)
{
    x = X;
    y = Y;
}

unsigned short PawnPos::X()
{
    return x;
}

unsigned short PawnPos::Y()
{
    return y;
}

void PawnPos::SetX(const unsigned short X)
{
    if (((y+1) % 2 == 1)&&((X+1) % 2 == 1))
    {
          qDebug() << "ERROR! PawnPos::SetX(const unsigned short X) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((X+1) % 2 == 0))
    {
         qDebug() << "ERROR! PawnPos::SetX(const unsigned short X) Try to set pawn on white field!";
    } else
    {
        x = X;
    };
}

void PawnPos::SetY(const unsigned short Y)
{
    if (((Y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
          qDebug() << "ERROR! PawnPos::SetY(const unsigned short Y) Try to set pawn on white field!";
    } else
    if (((Y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
         qDebug() << "ERROR! PawnPos::SetY(const unsigned short Y) Try to set pawn on white field!";
    } else
    {
        y = Y;
    };
}
