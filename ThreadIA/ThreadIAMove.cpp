#include "ThreadIA/ThreadIAMove.h"

template  <unsigned long int QMain>
ThreadIAMove<QMain>::ThreadIAMove()
{

}


template  <unsigned long int QMain>
void ThreadIAMove<QMain>::operator ()(Board * boardWsk)
{
    //Create first elements
    queue.PushBack(*boardWsk);
    CreateFirstElements();

    //Set origin to all
    SetOriginToAll();



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
        queue.PushBack(temp);
    }
}
