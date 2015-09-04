#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QPoint>
#include <thread>
#include <atomic>
#include <mutex>
#include "Traces/Traces.h"
#include "Pawn.h"
#include "PawnPos.h"
#include "ThreadIA/ThreadIASimpleBoard.h"

class ThreadIASimpleBoard;

class Board
{   
    public:
        Board();               
        void Clear();
        void SetWhitePawnPos(const unsigned short number,const unsigned short x, const unsigned short y);
        void SetBlackPawnPos(const unsigned short number,const unsigned short x, const unsigned short y);
        void PutWhiteTopLeftPawn(const unsigned short number);
        void PutWhiteTopRightPawn(const unsigned short number);
        void PutWhiteBottomLeftPawn(const unsigned short number);
        void PutWhiteBottomRightPawn(const unsigned short number);
        void PutBlackTopLeftPawn(const unsigned short number);
        void PutBlackTopRightPawn(const unsigned short number);
        void PutBlackBottomLeftPawn(const unsigned short number);
        void PutBlackBottomRightPawn(const unsigned short number);

        PawnPos GetWhitePawnPos(const unsigned short number);
        PawnPos GetBlackPawnPos(const unsigned short number);
        void RemoveBlackPawn(const unsigned short number);
        void RemoveWhitePawn(const unsigned short number);
        unsigned short GetWhitePawnNumber(const unsigned short x, const unsigned short y);
        unsigned short GetBlackPawnNumber(const unsigned short x, const unsigned short y);
        bool GetWhitePawnPons(const unsigned short number);
        bool GetBlackPawnPons(const unsigned short number);
        bool SetWhitePawnPons(const unsigned short number, const bool flag);
        bool SetBlackPawnPons(const unsigned short number, const bool flag);
        bool IsPawnOnPos(const unsigned short x, const unsigned short y);
        bool IsWhitePawnOnPos(const unsigned short x, const unsigned short y);
        bool IsBlackPawnOnPos(const unsigned short x, const unsigned short y);
        unsigned short GetNumberOfWhite();
        unsigned short GetNumberOfBlack();
        void RemovePawnFrom(const unsigned short x, const unsigned short y);

        void SetPreviousMurder(const unsigned short number);
        unsigned short GetPreviousMurder();

        unsigned short GetResult();
        double GetPercentageResult();
        void printDebug();

        Board & operator =(char *);
        Board & operator =(std::string);
        bool operator ==(Board );
        void CopyTo(ThreadIASimpleBoard & data);
        void CopyFrom(const ThreadIASimpleBoard & data);
        void SetOrigin(Board & data);
        Board GetOrigin();

        void StartBlack();
        void StartWhite();
        bool Black();
        bool White();
        bool GetNullBoard();
        void SetNullBoard(const bool flag);

    private:
        unsigned short numberOfWhite();
        unsigned short numberOfBlack();
        void eraseWhite(unsigned short num);
        void eraseBlack(unsigned short num);
        void clearWhite();
        void clearBlack();

        unsigned short previousMurder;
        ThreadIASimpleBoard origin;

        bool blackWhite;
        bool nullBoard;

        Pawn white[12];
        Pawn black[12];        
};

#endif // BOARD_H
