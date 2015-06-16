#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QPoint>
#include <QDebug>
#include "Pawn.h"
#include "PawnPos.h"

class Board
{   
    public:
        Board();
        void Clear();
        void SetWhitePawnPos(const unsigned short number,const unsigned short x, const unsigned short y);
        void SetBlackPawnPos(const unsigned short number,const unsigned short x, const unsigned short y);
        PawnPos GetWhitePawnPos(const unsigned short number);
        PawnPos GetBlackPawnPos(const unsigned short number);
        void RemoveBlackPawn(const unsigned short number);
        void RemoveWhitePawn(const unsigned short number);
        unsigned short GetWhitePawnNumber(const unsigned short x, const unsigned short y);
        unsigned short GetBlackPawnNumber(const unsigned short x, const unsigned short y);
        bool GetWhitePawnPons(const unsigned short number);
        bool GetBlackPawnPons(const unsigned short number);
        bool IsPawnOnPos(const unsigned short x, const unsigned short y);
        bool IsWhitePawnOnPos(const unsigned short x, const unsigned short y);
        bool IsBlackPawnOnPos(const unsigned short x, const unsigned short y);
        unsigned short GetNumberOfWhite();
        unsigned short GetNumberOfBlack();
        void RemovePonsFrom(const unsigned short x, const unsigned short y);

    private:
        unsigned short numberOfWhite;
        unsigned short numberOfBlack;
        std::vector<Pawn> white;
        std::vector<Pawn> black;

};

#endif // BOARD_H
