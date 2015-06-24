#ifndef IATREEEXPANDER_H
#define IATREEEXPANDER_H

#include "IA/IADecisionTree.h"
#include "IA/IAPossibleMoves.h"
#include "IA/IABoardQueue.h"
#include "Board.h"

class IATreeExpander
{
    public:
        IATreeExpander();
        Board ExpandTheTree(IADecisionTree *treePointer);

    private:
        bool ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue);
        bool ExpandBlack(IADecisionTree *treePointer, IABoardQueue &queue);        
};

#endif // IATREEEXPANDER_H
