#ifndef IABOARDQUEUE_H
#define IABOARDQUEUE_H

#include "IA/IADecisionTree.h"

class IABoardQueue
{
    public:
        IABoardQueue();
        void PushBack(IADecisionTree *wsk);
        IADecisionTree * PopFirst();
        ~IABoardQueue();
    private:
        std::list<IADecisionTree*> queue;
};

#endif // IABOARDQUEUE_H
