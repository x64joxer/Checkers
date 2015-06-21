#include "IABoardQueue.h"

IABoardQueue::IABoardQueue()
{
       test = 12;
}

void IABoardQueue::ForcePushBack(IADecisionTree *wsk)
{
    queue.push_back(wsk);
}

IADecisionTree * IABoardQueue::GetBestResult()
{
    qDebug() << "LOG: IABoardQueue::GetBestResult()";
    IADecisionTree * best = queue.front();
    foreach (IADecisionTree *wsk, queue)
    {
        if (best->GetBoard().GetNumberOfBlack()>wsk->GetBoard().GetNumberOfBlack())
        {
           best = wsk;
        };
    };

    qDebug() << "LOG: Best result:";
    best->GetBoard().printDebug();

    return best;
}

void IABoardQueue::PushBack(IADecisionTree *wsk)
{
    //Mutex
    //Test
    Board board = wsk->GetBoard();
    if (wsk->Black())
    {
        if (board.GetNumberOfBlack()<test)
        {
            queue.clear();
            test = board.GetNumberOfBlack();
            queue.push_back(wsk);
        } else
        {
            queue.push_back(wsk);
        };
    } else
    if (wsk->White())
    {
        if (board.GetNumberOfBlack()==test)
        {
            queue.push_back(wsk);
        } else
        {
            queue.push_back(wsk);
        };
    };

    qDebug() << "LOG: Queue size:" << queue.size();
    //Test




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
