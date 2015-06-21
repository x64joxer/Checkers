#ifndef IADECISIONTREE_H
#define IADECISIONTREE_H

#include <list>
#include "Board.h"

class IADecisionTree
{
    public:
        IADecisionTree();
        ~IADecisionTree();
        bool Black();
        bool White();
        void SetBoard(Board &b);
        void SetPreviousElement(IADecisionTree *wsk);
        IADecisionTree * GetPreviousElement();
        void StartBlack();
        void StartWhite();
        Board GetBoard();
        IADecisionTree * AddNextStep(Board b,const bool blackWhte, const unsigned short number = 9);
        void SetPreviousMurder(const unsigned short number);
        unsigned short GetPreviousMurder();

    private:
        Board board;
        unsigned short previousMurder;
        bool blackWhite;
        IADecisionTree *previous;
        std::list<IADecisionTree*> next;

        static unsigned int numberOfElelments;
};

#endif // IADECISIONTREE_H
