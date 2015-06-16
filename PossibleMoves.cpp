#include "PossibleMoves.h"

PossibleMoves::PossibleMoves()
{

}

bool PossibleMoves::CanIGrab(const unsigned short number, Board board)
{
    PawnPos pos = board.GetBlackPawnPos(number);
    bool flag = CheckHitTopLeft(pos.X(), pos.Y(), board) | CheckHitTopRight(pos.X(), pos.Y(), board);
    qDebug() << "CheckHitTopLeft(pos.X(), pos.Y(), board) " << CheckHitTopLeft(pos.X(), pos.Y(), board);
    qDebug() << "CheckHitTopRight(pos.X(), pos.Y(), board" << CheckHitTopRight(pos.X(), pos.Y(), board);
    bool otherFlag = false;
    for (unsigned short i=0; i < board.GetNumberOfBlack();i++)
    {
        if (i!=number)
        {
            PawnPos pos = board.GetBlackPawnPos(i);
            otherFlag = otherFlag | CheckHitTopLeft(pos.X(), pos.Y(), board) | CheckHitTopRight(pos.X(), pos.Y(), board);
        };
    };

    qDebug() << "otherFlag " << otherFlag;

    if (!flag)
    {
        if (otherFlag)
        {
            return false;
        };
    };

    if (flag) return 1;
    return CheckPutTopLeft(pos.X(), pos.Y(), board) | CheckPutTopRight(pos.X(), pos.Y(), board);
}


bool PossibleMoves::CheckHitTopLeft(const unsigned short x, const unsigned short y, Board board)
{
    if (OutOfBoard(x-1, y - 1)) return 0;
    if (!board.IsWhitePawnOnPos(x-1,y-1))
    {
        return 0;
    } else
    {
        if (OutOfBoard(x-2, y - 2)) return 0;
        if (board.IsPawnOnPos(x-2,y-2)) return 0;
        return 1;
    };
}

bool PossibleMoves::CheckHitTopRight(const unsigned short x, const unsigned short y, Board board)
{
    if (OutOfBoard(x+1, y -1)) return 0;
    if (!board.IsWhitePawnOnPos(x+1,y-1))
    {
        return 0;
    } else
    {
        if (OutOfBoard(x +2, y -2)) return 0;
        if (board.IsPawnOnPos(x+2,y-2)) return 0;
        return 1;
    };
}

bool PossibleMoves::CheckPutTopLeft(const unsigned short x, const unsigned short y, Board board)
{
    if (OutOfBoard(x-1, y -1)) return 0;
    if (board.IsPawnOnPos(x-1, y -1)) return 0;
    return true;
}

bool PossibleMoves::CheckPutTopRight(const unsigned short x, const unsigned short y, Board board)
{
    if (OutOfBoard(x+1, y -1)) return 0;
    if (board.IsPawnOnPos(x+1, y -1)) return 0;
    return true;
}

bool PossibleMoves::CanIPutHere(const unsigned short number, const unsigned short x, const unsigned short y, Board board)
{
    PawnPos pos = board.GetBlackPawnPos(number);
    if ((x == pos.X()-2)&&(y == pos.Y()-2))
    {
        if (CheckHitTopLeft(pos.X(), pos.Y(), board))
        {
            return 1;
        };
    };

    if ((x == pos.X()+2)&&(y == pos.Y()-2))
    {
        if (CheckHitTopRight(pos.X(), pos.Y(), board))
        {
            return 1;
        };
    };

    if ((x == pos.X()-1)&&(y == pos.Y()-1))
    {
        if (CheckPutTopLeft(pos.X(), pos.Y(), board))
        {
            return 1;
        };
    };

    if ((x == pos.X()+1)&&(y == pos.Y()-1))
    {
        if (CheckPutTopRight(pos.X(), pos.Y(), board))
        {
            return 1;
        };
    };

    return false;
}

bool PossibleMoves::IsKill(const unsigned short number, const unsigned short x, const unsigned short y, Board board, unsigned short &killed)
{
    PawnPos pos = board.GetBlackPawnPos(number);
    if ((x == pos.X()-2)&&(y == pos.Y()-2))
    {
        if (CheckHitTopLeft(pos.X(), pos.Y(), board))
        {
            killed = board.GetWhitePawnNumber(pos.X()-1, pos.Y() -1);
            return 1;
        };
    };

    if ((x == pos.X()+2)&&(y == pos.Y()-2))
    {
        if (CheckHitTopRight(pos.X(), pos.Y(), board))
        {
            killed = board.GetWhitePawnNumber(pos.X()+1, pos.Y() -1);
            return 1;
        };
    };

    return 0;
}

bool PossibleMoves::OutOfBoard(const unsigned short x, const unsigned short y)
{
    if (x<0) return 1;
    if (x>7) return 1;
    if (y<0) return 1;
    if (y>7) return 1;

    return 0;
}


