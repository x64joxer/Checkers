#ifndef THREADIABOARDQUEUE_H
#define THREADIABOARDQUEUE_H

#include <mutex>
#include <condition_variable>
#include "Board.h"
#include "Traces/Traces.h"
#include "ProgramVariables.h"

template <unsigned long long size>
class ThreadIABoardQueue
{
    public:
        ThreadIABoardQueue();
        ~ThreadIABoardQueue();
        Board PopFront(const unsigned short num);
        inline void PushBack(Board &board);
        inline void PushBackDoNotForget(Board &board);
        Board GetBestResult();
        void GetBestResult2(bool make, const unsigned int start, const unsigned int stop, bool make2, const unsigned int start2, const unsigned int stop2, Board *best);
        void Clear();
        Board First(const bool remove);      
        unsigned long long GetFirstNumber();
        void NotifyRest();
        unsigned long long Size();
        unsigned long long SizeDoNotForget();
        Board & At(const unsigned long long number);

    private:
        bool Empty() { if (numberOfElements==0) { return true;}; return false;  }
        void SetWorkerFlag(const bool flag,const unsigned short number);

        Board *queue;        
        unsigned long long first;
        unsigned long long last;
        unsigned long long numberOfElements;

        Board *doNotForgetqueue;
        unsigned long long doNotForgetnumberOfElements;

        std::mutex mutex_guard;
        std::condition_variable *condition_var;
        unsigned short workersFlags;
};

#endif // THREADIABOARDQUEUE_H
