#ifndef IATREEEXPANDER_H
#define IATREEEXPANDER_H

#include "IA/IADecisionTree.h"
#include "IA/IAPossibleMoves.h"
#include "Board.h"

class IATreeExpander
{
    public:
        IATreeExpander();
        void ExpandTheTree(IADecisionTree *treePointer);

    private:
        bool ExpandWhite(IADecisionTree *treePointer);
};

#endif // IATREEEXPANDER_H
