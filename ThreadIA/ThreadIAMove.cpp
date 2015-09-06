#include "ThreadIA/ThreadIAMove.h"

template  <unsigned long int QMain>
ThreadIAMove<QMain>::ThreadIAMove()
{

}


template  <unsigned long int QMain>
void ThreadIAMove<QMain>::operator ()(Board * boardWsk, std::atomic_bool * flag, std::atomic<int> *percentSteps)
{
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

        //ThreadIATreeExpander<QMain,5000> expander;

        ThreadIATreeExpander<QMain,5000> expander1;
        ThreadIATreeExpander<QMain,5000> expander2;

        expander1.mainBoardQueue_2 = &queue;
        expander2.mainBoardQueue_2 = &queue;


        std::thread job1(&ThreadIATreeExpander<QMain,5000>::ExpandWithoutQueue,
                         &expander1,
                         1000,
                         3000
                         );

        std::thread job2(&ThreadIATreeExpander<QMain,5000>::ExpandWithoutQueue,
                         &expander1,
                         1000,
                         3000
                         );

        job1.join();
        job2.join();

        //expander.Expand(9000,3000,queue);

        temp = queue.GetBestResult();

        queue.Clear();
        *boardWsk = temp.GetOrigin();

        Traces() << "\n" << "LOG: Best board set:";
        temp.printDebug();
        boardWsk->printDebug();


        *flag = true;        
    };    
  Traces::GetCurrentTime();
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
