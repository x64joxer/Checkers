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
        void AddBlackPawn(const unsigned short x, const unsigned short y, const bool dead, const bool pons);
        void AddWhitePawn(const unsigned short x, const unsigned short y, const bool dead, const bool pons);
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

        PawnPos GetWhitePawnPos(const unsigned short number) const;
        PawnPos GetBlackPawnPos(const unsigned short number) const;
        void RemoveBlackPawn(const unsigned short number);
        void RemoveWhitePawn(const unsigned short number);
        unsigned short GetWhitePawnNumber(const unsigned short x, const unsigned short y) const;
        unsigned short GetBlackPawnNumber(const unsigned short x, const unsigned short y) const;
        bool GetWhitePawnPons(const unsigned short number) const;
        bool GetBlackPawnPons(const unsigned short number) const;
        bool SetWhitePawnPons(const unsigned short number, const bool flag);
        bool SetBlackPawnPons(const unsigned short number, const bool flag);
        bool IsPawnOnPos(const unsigned short x, const unsigned short y) const;
        bool IsWhitePawnOnPos(const unsigned short x, const unsigned short y) const;
        bool IsBlackPawnOnPos(const unsigned short x, const unsigned short y) const;
        unsigned short GetNumberOfWhite() const;
        unsigned short GetNumberOfBlack() const;
        void RemovePawnFrom(const unsigned short x, const unsigned short y);

        void SetPreviousMurder(const unsigned short number);
        unsigned short GetPreviousMurder() const;

        unsigned short GetResult() const;
        double GetPercentageResult() const;
        void printDebug() const;

        Board & operator =(char *);
        Board & operator =(std::string);
        bool operator ==(Board );
        bool operator !=(Board );
        void CopyTo(ThreadIASimpleBoard & data);
        void CopyFrom(const ThreadIASimpleBoard & data);
        void SetOrigin(Board & data);
        Board GetOrigin() const;

        void StartBlack();
        void StartWhite();
        bool Black() const;
        bool White() const;
        bool GetNullBoard() const;
        void SetNullBoard(const bool flag);
        bool GetWhitePatchEnd() const;
        void SetWhitePatchEnd(const bool flag);

    private:
        unsigned short numberOfWhite() const;
        unsigned short numberOfBlack() const;
        void eraseWhite(unsigned short num);
        void eraseBlack(unsigned short num);
        void clearWhite();
        void clearBlack();

        unsigned short previousMurder;
        ThreadIASimpleBoard origin;
        bool whitePatchEnd;

        bool blackWhite;
        bool nullBoard;

        Pawn white[12];
        Pawn black[12];        
};

#endif // BOARD_H
