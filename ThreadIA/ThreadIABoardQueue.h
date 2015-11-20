#ifndef THREADIABOARDQUEUE_H
#define THREADIABOARDQUEUE_H

#include <mutex>
#include <condition_variable>
#include "Board.h"
#include "Traces/Traces.h"
#include "ProgramVariables.h"

template <unsigned long int size>
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
        Board PopFirst();
        unsigned long int GetFirstNumber();
        void NotifyRest();
        unsigned long int Size();
        unsigned long int SizeDoNotForget();

    private:
        bool Empty() { if (numberOfElements==0) { return true;}; return false;  }
        void SetWorkerFlag(const bool flag,const unsigned short number);

        Board *queue;        
        unsigned long int first;
        unsigned long int last;
        unsigned long int numberOfElements;

        Board *doNotForgetqueue;
        unsigned long int doNotForgetnumberOfElements;

        std::mutex mutex_guard;
        std::condition_variable *condition_var;
        unsigned short workersFlags;
};

#endif // THREADIABOARDQUEUE_H
