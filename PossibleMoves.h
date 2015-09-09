#ifndef POSSIBLEMOVES_H
#define POSSIBLEMOVES_H

#include <list>
#include "Board.h"

class PossibleMoves
{
    public:
        PossibleMoves();
        bool CanIGrab(const unsigned short number, Board board);
        bool CheckHitTopLeft(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitTopRight(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomLeft(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomRight(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopLeft(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopRight(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomLeft(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomRight(const unsigned short x, const unsigned short y, Board board);
        bool CanIPutHere(const unsigned short number, const unsigned short x, const unsigned short y, Board board);
        bool IsKill(const unsigned short number, const unsigned short x, const unsigned short y, Board board, unsigned short &killed);

    private:

        bool OutOfBoard(const unsigned short x, const unsigned short y);

};

#endif // POSSIBLEMOVES_H
