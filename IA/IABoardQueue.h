#ifndef IABOARDQUEUE_H
#define IABOARDQUEUE_H

#include "IA/IADecisionTree.h"
#include "Traces/Traces.h"
#include <mutex>

class IABoardQueue
{
    public:
        IABoardQueue();
        int PushBack(IADecisionTree *wsk);
        int PushBackDoNotForget(IADecisionTree *wsk);
        void ForcePushBack(IADecisionTree *wsk);
        IADecisionTree * GetBestResult();
        IADecisionTree * PopFirst();
        void TryTransfer(IABoardQueue *wsk, unsigned int count);
        int Size();
        ~IABoardQueue();
    private:
        std::list<IADecisionTree*> queue;
        std::list<IADecisionTree*> doNotForgetQueue;
        unsigned short test;
        std::mutex *mutex;
};

#endif // IABOARDQUEUE_H
