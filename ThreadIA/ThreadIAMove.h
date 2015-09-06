#ifndef THREADIAMOVE_H
#define THREADIAMOVE_H

#include <atomic>
#include "Board.h"
#include "ThreadIA/ThreadIABoardQueue.h"
#include "ThreadIA/ThreadIABoardQueue.cpp"
#include "ThreadIA/ThreadIATreeExpander.cpp"

template <unsigned long int QMain>
class ThreadIAMove
{
    public:
        ThreadIAMove();
        void operator ()(Board * boardWsk, std::atomic_bool * flag, std::atomic<int> *percentSteps, const unsigned short numberOfThreads, const unsigned int refreshMainQueue, const unsigned int numberOfStepsToDo);
   private:
        ThreadIABoardQueue<QMain> queue;
        void CreateFirstElements();
        void SetOriginToAll();

};

#endif // THREADIAMOVE_H
