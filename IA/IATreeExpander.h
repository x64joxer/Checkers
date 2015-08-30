#ifndef IATREEEXPANDER_H
#define IATREEEXPANDER_H

#include <chrono>
#include <atomic>
#include "IA/IADecisionTree.h"
#include "IA/IAPossibleMoves.h"
#include "IA/IABoardQueue.h"
#include "Board.h"

class IATreeExpander
{
    public:
        IATreeExpander();
        void Move(Board * boardRef, std::atomic_bool * flag, std::atomic<int> *percentSteps);
        Board ExpandTheTree(IADecisionTree *treePointer, std::atomic<int> *percentSteps);
        Board ExpandTheTreeSingleThread(IADecisionTree *treePointer);
        Board ExpandTheTreeMultiThread(IADecisionTree *treePointer);

    private:
        bool ExpandWhite(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber = 1);
        bool ExpandBlack(IADecisionTree *treePointer, IABoardQueue &queue, unsigned int stepNumber = 1);

        bool singleThread;
        int currentStep;
        int numberOfSteps;
        std::atomic<int> *currentPercentSteps;
};

#endif // IATREEEXPANDER_H
