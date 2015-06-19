#ifndef IAPOSSIBLEMOVES_H
#define IAPOSSIBLEMOVES_H

#include "Board.h"
#include "PawnPos.h"

class IAPossibleMoves
{
    public:
        IAPossibleMoves();
        bool CanIGrabBlack(const unsigned short number, Board board);
        bool CheckHitTopLeftBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitTopRightBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomLeftBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomRightBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopLeftBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopRightBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomLeftBlack(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomRightBlack(const unsigned short x, const unsigned short y, Board board);
        bool CanIPutHereBlack(const unsigned short number, const unsigned short x, const unsigned short y, Board board);
        bool IsKillBlack(const unsigned short number, const unsigned short x, const unsigned short y, Board board, unsigned short &killed);
        bool OutOfBoardBlack(const unsigned short x, const unsigned short y);
        bool CanIGrabWhite(const unsigned short number, Board board);

        bool CheckHitTopLeftWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitTopRightWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomLeftWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckHitBottomRightWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopLeftWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutTopRightWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomLeftWhite(const unsigned short x, const unsigned short y, Board board);
        bool CheckPutBottomRightWhite(const unsigned short x, const unsigned short y, Board board);

        //New
        bool CheckHitTopLeftWhite(const unsigned short number, Board board);
        bool CheckHitTopRightWhite(const unsigned short number, Board board);
        bool CheckHitBottomLeftWhite(const unsigned short number, Board board);
        bool CheckHitBottomRightWhite(const unsigned short number, Board board);
        bool CheckPutTopLeftWhite(const unsigned short number, Board board);
        bool CheckPutTopRightWhite(const unsigned short number, Board board);
        bool CheckPutBottomLeftWhite(const unsigned short number, Board board);
        bool CheckPutBottomRightWhite(const unsigned short number, Board board);

        void KillHitTopLeftWhite(const unsigned short number, Board &board);
        void KillHitTopRightWhite(const unsigned short number, Board &board);
        void KillHitBottomLeftWhite(const unsigned short number, Board &board);
        void KillHitBottomRightWhite(const unsigned short number, Board &board);
        //End New
        //NEW
        bool CheckHitTopLeftBlack(const unsigned short number, Board board);
        bool CheckHitTopRightBlack(const unsigned short number, Board board);
        bool CheckHitBottomLeftBlack(const unsigned short number, Board board);
        bool CheckHitBottomRightBlack(const unsigned short number, Board board);
        bool CheckPutTopLeftBlack(const unsigned short number, Board board);
        bool CheckPutTopRightBlack(const unsigned short number, Board board);
        bool CheckPutBottomLeftBlack(const unsigned short number, Board board);
        bool CheckPutBottomRightBlack(const unsigned short number, Board board);

        void KillHitTopLeftBlack(const unsigned short number, Board &board);
        void KillHitTopRightBlack(const unsigned short number, Board &board);
        void KillHitBottomLeftBlack(const unsigned short number, Board &board);
        void KillHitBottomRightBlack(const unsigned short number, Board &board);
        //NEW
        bool CanIPutHereWhite(const unsigned short number, const unsigned short x, const unsigned short y, Board board);
        bool IsKillWhite(const unsigned short number, const unsigned short x, const unsigned short y, Board board, unsigned short &killed);
        bool OutOfBoardWhite(const unsigned short x, const unsigned short y);

};


#endif // IAPOSSIBLEMOVES_H
