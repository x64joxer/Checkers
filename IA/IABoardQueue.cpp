#include "IABoardQueue.h"

IABoardQueue::IABoardQueue()
{
       test = 12;
       mutex = new std::mutex();
}

void IABoardQueue::ForcePushBack(IADecisionTree *wsk)
{
    std::unique_lock<std::mutex> guard(*mutex);
    queue.push_back(wsk);
}

IADecisionTree * IABoardQueue::GetBestResult()
{
    std::unique_lock<std::mutex> guard(*mutex);
    Traces() << "\n" << "LOG: IABoardQueue::GetBestResult()";
    Traces() << "LOG: queue.size()=" << queue.size();
    Traces() << "LOG: doNotForgetQueue.size()=" << doNotForgetQueue.size();

    IADecisionTree * best;

    if ((queue.empty())&&(doNotForgetQueue.empty())) return nullptr;

    if (queue.size()==1)
    {
        best = queue.front();
    } else
    if (queue.size()>1)
    {
        best = queue.front();
        foreach (IADecisionTree *wsk, queue)
        {           
            if (best->GetBoard().GetPercentageResult()>wsk->GetBoard().GetPercentageResult())
            {
               best = wsk;
            };
        };
    };

    if (doNotForgetQueue.size()==1)
    {
        best = doNotForgetQueue.front();
    } else
    if (doNotForgetQueue.size()>1)
    {
        best = doNotForgetQueue.front();
        foreach (IADecisionTree *wsk, doNotForgetQueue)
        {
            if (best->GetBoard().GetPercentageResult()>wsk->GetBoard().GetPercentageResult())
            {
               best = wsk;
            };
        };
    };

    Traces() << "\n" << "LOG: Best result:";
    best->GetBoard().printDebug();

    return best;
}

int IABoardQueue::PushBack(IADecisionTree *wsk)
{
    queue.push_back(wsk);
    std::unique_lock<std::mutex> guard(*mutex);
    //Test
    /*if (queue.size() == 0)
    {
        Traces() << "\n" << "LOG: IABoardQueue::PushBack(IADecisionTree *wsk) List empty, push front";
        queue.push_front(wsk);
        return 0;
    };

    if (wsk->GetPreviousElement()->White())
    {
        if (wsk->GetBoard().GetNumberOfWhite()<wsk->GetPreviousElement()->GetBoard().GetNumberOfWhite())
        {
            queue.push_back(wsk);
            return 0;
        };
    };

    Board board = wsk->GetBoard();
    IADecisionTree *tempWsk = queue.front();

    if (tempWsk->GetBoard().GetResult() <= board.GetResult())
    {
        Traces() << "\n" << "LOG: IABoardQueue::PushBack(IADecisionTree *wsk) Push first";
        queue.push_front(wsk);
    } else
    {
        Traces() << "\n" << "LOG: IABoardQueue::PushBack(IADecisionTree *wsk) Push second first";
        queue.pop_front();
        queue.push_front(wsk);
        queue.push_front(tempWsk);

    };*/

    /*if (wsk->Black())
    {
        if (board.GetNumberOfBlack()<test)
        {
            queue.clear();
            test = board.GetNumberOfBlack();
            queue.push_front(wsk);
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
    };*/

    Traces() << "\n" << "LOG: Queue size:" << queue.size();
    return 0;
    //Test    
}

int IABoardQueue::PushBackDoNotForget(IADecisionTree *wsk)
{
    std::unique_lock<std::mutex> guard(*mutex);
    doNotForgetQueue.push_back(wsk);    
}

int IABoardQueue::Size()
{
    std::unique_lock<std::mutex> guard(*mutex);
    return queue.size();
}

IADecisionTree * IABoardQueue::PopFirst()
{    
    std::unique_lock<std::mutex> guard(*mutex);
    if (queue.empty()) return nullptr;

    std::list<IADecisionTree*>::iterator iter = queue.begin();
    bool flag = false;
    IADecisionTree * wsk = *iter;
    int size = queue.size() -1;    

    do
    {
        queue.pop_front();
        flag = false;

        if (wsk->GetBoard().GetNumberOfBlack() == 0)
        {
            queue.push_back(wsk);
            flag = true;
        } else
        if (wsk->GetBoard().GetNumberOfWhite() == 0)
        {
            queue.push_back(wsk);
            flag = true;
        };

        size--;
        if ((size <= 0)&&(flag))
        {
            flag = false;
            wsk = nullptr;
        };

        if (flag)
        {
            iter = queue.begin();
            wsk = *iter;
        };

    } while (flag);

    return wsk;
}

void IABoardQueue::TryTransfer(IABoardQueue *wsk, unsigned int count)
{
    std::unique_lock<std::mutex> guard(*mutex);
    Traces() << "\n" << "LOG: IABoardQueue::TryTransfer(IABoardQueue *wsk, unsigned int count) Trying to transfer " << count << " jobs";

    if (count == 0) count = queue.size();

    if (queue.size()>=count)
    {
        Traces() << "\n" << "LOG: Succes transfering jobs.";

        for (int i=0;i< count;i++)
        {
            wsk->PushBack(queue.front());
            queue.pop_front();
        };
    } else
    {
        Traces() << "\n" << "LOG: No jobs. Number of current jobs " << queue.size();
    };
}

IABoardQueue::~IABoardQueue()
{
    std::unique_lock<std::mutex> guard(*mutex);
    queue.clear();
}
