#ifndef IABOARDQUEUE_H
#define IABOARDQUEUE_H

#include "IA/IADecisionTree.h"
#include "Traces/Traces.h"

class IABoardQueue
{
    public:
        IABoardQueue();
        int PushBack(IADecisionTree *wsk);
        int PushBackDoNotForget(IADecisionTree *wsk);
        void ForcePushBack(IADecisionTree *wsk);
        IADecisionTree * GetBestResult();
        IADecisionTree * PopFirst();
        ~IABoardQueue();
    private:
        std::list<IADecisionTree*> queue;
        std::list<IADecisionTree*> doNotForgetQueue;
        unsigned short test;
};

#endif // IABOARDQUEUE_H
