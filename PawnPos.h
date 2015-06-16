#ifndef PAWNPOS_H
#define PAWNPOS_H

#include <QDebug>

class PawnPos
{
    public:
        PawnPos();
        PawnPos(const int X, const int Y);
        unsigned short X();
        unsigned short Y();
        void SetX(const unsigned short X);
        void SetY(const unsigned short Y);
    private:
        unsigned short x : 4;
        unsigned short y : 4;
};

#endif // PAWNPOS_H
