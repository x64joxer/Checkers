#include "IABoardQueue.h"

IABoardQueue::IABoardQueue()
{

}

void IABoardQueue::PushBack(IADecisionTree *wsk)
{
    //Mutex
    queue.push_back(wsk);
    //Mutex
}

IADecisionTree * IABoardQueue::PopFirst()
{
    //Mutex
    std::list<IADecisionTree*>::iterator iter = queue.begin();
    IADecisionTree * wsk = *iter;
    queue.pop_front();
    //Mutex
    return wsk;
}

IABoardQueue::~IABoardQueue()
{
    queue.clear();
}
