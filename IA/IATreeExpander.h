#ifndef IATREEEXPANDER_H
#define IATREEEXPANDER_H

#include <chrono>
#include "IA/IADecisionTree.h"
#include "IA/IAPossibleMoves.h"
#include "IA/IABoardQueue.h"
#include "Board.h"

class IATreeExpander
{
    public:
        IATreeExpander();
        Board ExpandTheTree(IADecisionTree *treePointer);
        Board ExpandTheTreeSingleThread(IADecisionTree *treePointer);
        Board ExpandTheTreeMultiThread(IADecisionTree *treePointer);

    private:
        bool ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber = 1);
        bool ExpandBlack(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber = 1);

        bool singleThread;
        int numberOfSteps;
};

#endif // IATREEEXPANDER_H
