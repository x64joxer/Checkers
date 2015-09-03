#ifndef THREADIABOARDQUEUE_H
#define THREADIABOARDQUEUE_H

#include "Board.h"
#include "Traces/Traces.h"

template <unsigned long int size>
class ThreadIABoardQueue
{
    public:
        ThreadIABoardQueue();
        Board PopFront();
        inline void PushBack(Board &board);
    private:
        Board queue[size];
        unsigned long int first;
        unsigned long int last;
        unsigned long int numberOfElements;
};

#endif // THREADIABOARDQUEUE_H
