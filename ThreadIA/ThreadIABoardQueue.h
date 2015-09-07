#ifndef THREADIABOARDQUEUE_H
#define THREADIABOARDQUEUE_H

#include <mutex>
#include <condition_variable>
#include "Board.h"
#include "Traces/Traces.h"

template <unsigned long int size>
class ThreadIABoardQueue
{
    public:
        ThreadIABoardQueue();
        ~ThreadIABoardQueue();
        Board PopFront();
        inline void PushBack(Board &board);
        inline void PushBackDoNotForget(Board &board);
        Board GetBestResult();
        void Clear();
        Board First();
        unsigned long int Size();
    private:
        bool Empty() { if (numberOfElements==0) { return true;}; return false;  }

        Board *queue;        
        unsigned long int first;
        unsigned long int last;
        unsigned long int numberOfElements;

        Board *doNotForgetqueue;
        unsigned long int doNotForgetnumberOfElements;

        std::mutex mutex_guard;
        bool mutex_flag;
        std::condition_variable condition_var;
};

#endif // THREADIABOARDQUEUE_H
