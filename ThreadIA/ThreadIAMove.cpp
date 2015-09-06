#include "ThreadIA/ThreadIAMove.h"

template  <unsigned long int QMain>
ThreadIAMove<QMain>::ThreadIAMove()
{

}


template  <unsigned long int QMain>
void ThreadIAMove<QMain>::operator ()(Board * boardWsk, std::atomic_bool * flag, std::atomic<int> *percentSteps, const unsigned short numberOfThreads, const unsigned int refreshMainQueue, const unsigned int numberOfStepsToDo)
{
    const unsigned short maxThreads = 5;
    std::thread iaThread[maxThreads];
    ThreadIATreeExpander<QMain,5000> expander[maxThreads];
    unsigned int numberOfSteps = numberOfStepsToDo / numberOfThreads;

    //Create first elements
    Board temp = *boardWsk;
    temp.StartWhite();
    temp.SetWhitePatchEnd(false);

    queue.PushBack(temp);
    CreateFirstElements();    


    //Can not move or all black killed
    if (queue.Size() == 0)
    {
        *flag = true;
    } else
    {
        //Set origin to all
        SetOriginToAll();

        //Start threads
        for (unsigned short i=1;i<=numberOfThreads;i++)
        {
            expander[i].mainBoardQueue_2 = &queue;
            iaThread[i] = std::move(std::thread(&ThreadIATreeExpander<QMain,5000>::ExpandWithoutQueue,
                                                &expander[i],
                                                numberOfSteps,
                                                refreshMainQueue
                                                ));

        };

        for (unsigned short i=1;i<=numberOfThreads;i++)
        {
            iaThread[i].join();
        };

        temp = queue.GetBestResult();

        queue.Clear();
        *boardWsk = temp.GetOrigin();

        Traces() << "\n" << "LOG: Best board set:";
        temp.printDebug();
        boardWsk->printDebug();


        *flag = true;        
    };    
  //Traces::GetCurrentTime();
}

template  <unsigned long int QMain>
void ThreadIAMove<QMain>::CreateFirstElements()
{
    ThreadIATreeExpander<QMain,36> expander;
    expander.Expand(1,100,queue);
}

template  <unsigned long int QMain>
void ThreadIAMove<QMain>::SetOriginToAll()
{
    Traces() << "\n" << "LOG: void ThreadIAMove<QMain>::SetOriginToAll()";
    unsigned long int size = queue.Size();
    Board temp;

    if (size>0)
    {
        for (unsigned int i=0;i<size;i++)
        {
            temp = queue.PopFront();
            temp.SetOrigin(temp);          

            Traces() << "\n" << "LOG: Origin set";
            temp.printDebug();
            queue.PushBack(temp);
        }
    };
}
