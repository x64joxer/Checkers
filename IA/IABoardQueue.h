#ifndef IABOARDQUEUE_H
#define IABOARDQUEUE_H

#include "IA/IADecisionTree.h"

class IABoardQueue
{
    public:
        IABoardQueue();
        void PushBack(IADecisionTree *wsk);
        void ForcePushBack(IADecisionTree *wsk);
        IADecisionTree * GetBestResult();
        IADecisionTree * PopFirst();
        ~IABoardQueue();
    private:
        std::list<IADecisionTree*> queue;
        unsigned short test;
};

#endif // IABOARDQUEUE_H
