#ifndef THREADIAMOVE_H
#define THREADIAMOVE_H

#include "Board.h"
#include "ThreadIA/ThreadIABoardQueue.h"
#include "ThreadIA/ThreadIATreeExpander.h"

template <unsigned long int QMain>
class ThreadIAMove
{
    public:
        ThreadIAMove();
        void operator ()(Board * boardWsk);
   private:
        ThreadIABoardQueue<QMain> queue;
        void CreateFirstElements();
        void SetOriginToAll();

};

#endif // THREADIAMOVE_H
