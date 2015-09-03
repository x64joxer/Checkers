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

    queue.PushBack(temp);
    CreateFirstElements();

    //Set origin to all
    SetOriginToAll();

    ThreadIATreeExpander<QMain,5000> expander;

    expander.Expand(100,3000,queue);

    temp = queue.GetBestResult();

    queue.Clear();
    *boardWsk = temp.GetOrigin();

    Traces() << "\n" << "LOG: Best board set:";
    temp.printDebug();
    boardWsk->printDebug();


    *flag = true;
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
    unsigned long int size = queue.Size();
    Board temp;

    for (unsigned int i=0;i<size;i++)
    {
        temp = queue.PopFront();
        temp.SetOrigin(temp);

        Traces() << "\n" << "LOG: Origin set";
        temp.printDebug();
        queue.PushBack(temp);
    }
}
