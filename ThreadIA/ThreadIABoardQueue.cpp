#include "ThreadIA/ThreadIABoardQueue.h"

template <unsigned long int size>
ThreadIABoardQueue<size>::ThreadIABoardQueue()
{
    first = 0;
    last = 0;
    numberOfElements = 0;    
    queue = new Board[size];

    doNotForgetqueue = new Board[size];
    doNotForgetnumberOfElements =0;
    mutex_flag = true;

   // mutex = new std::mutex();
}

template <unsigned long int size>
void ThreadIABoardQueue<size>::Clear()
{
    first = 0;
    last = 0;
    numberOfElements = 0;
    doNotForgetnumberOfElements =0;
    mutex_flag = true;
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::First()
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    return queue[first];
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::PopFront()
{    
    std::lock_guard<std::mutex> guard(mutex_guard);
    unsigned long int temp = first;
    Traces() << "\n" << "LOG: Board ThreadIABoardQueue<size>::PopFront()";
    if (numberOfElements>0)
    {
        Traces() << "\n" << "LOG: (numberOfElements>0)";

        if (numberOfElements>1)
        {
            first++;
            if (first==size)
            {
             first = 0;
            };
            numberOfElements--;

        } else
        {
            first = 0;
            last = 0;
            numberOfElements = 0;
        };

        Traces() << "\n" << "LOG: first " << first;
        Traces() << "\n" << "LOG: last " << last;
        Traces() << "\n" << "LOG: Number of cells " << numberOfElements;

        queue[temp].printDebug();
        return queue[temp];
    };

    Traces() << "\n" << "LOG: No elements to get!";
    Board temp_null;
    temp_null.SetNullBoard(true);    
    return temp_null;
}

template <unsigned long int size>
inline void ThreadIABoardQueue<size>::PushBack(Board & board)
{

    Traces() << "\n" << "LOG: void ThreadIABoardQueue<size>::PushBack(Board board) Number of cells";

    if (numberOfElements == 0)
    {
       numberOfElements++;
       queue[last] = board;

       Traces() << "\n" << "LOG: first " << first;
       Traces() << "\n" << "LOG: last " << last;
       Traces() << "\n" << "LOG: Number of cells " << numberOfElements;
    } else
    if (numberOfElements<=size)
    {
        Traces() << "\n" << "LOG: if (numberOfElements<=size)";
        if (last==size-1)
        {
            last = 0;
            queue[last] = board;
            numberOfElements++;
        } else
        {
            last++;
            queue[last] = board;
            numberOfElements++;
        };

        Traces() << "\n" << "LOG: first " << first;
        Traces() << "\n" << "LOG: last " << last;
        Traces() << "\n" << "LOG: Number of cells " << numberOfElements;
    } else
    {
        Traces() << "\n" << "ERROR: No more free cells!";
    };

}

template <unsigned long int size>
inline void ThreadIABoardQueue<size>::PushBackDoNotForget(Board &board)
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    Traces() << "\n" << "LOG: inline void ThreadIABoardQueue<size>::PushBackDoNotForget(Board &board)";
    doNotForgetqueue[doNotForgetnumberOfElements] = board;
    ++doNotForgetnumberOfElements;
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::GetBestResult()
{
    double result = 0;
    Board temp;

    if (numberOfElements>0)
    {
        result = queue[first].GetPercentageResult();
        temp = queue[first];
        PopFront();

        if (numberOfElements>0)
        {
            for (unsigned long int i=first;i<last;i++)
            {
                if (result>queue[i].GetPercentageResult())
                {
                    result =  queue[i].GetPercentageResult();
                    temp = queue[i];
                };
            };
        };
    }

    if (doNotForgetnumberOfElements>0)
    {
        result = doNotForgetqueue[0].GetPercentageResult();
        temp = doNotForgetqueue[0];

        Traces() << "\n" << "LOG: Origin of doNotForgetqueue[0]";
        doNotForgetqueue[0].GetOrigin().printDebug();


        if (doNotForgetnumberOfElements>1)
        {
            for (unsigned long int i=1;i<doNotForgetnumberOfElements;i++)
            {
                if (result>doNotForgetqueue[i].GetPercentageResult())
                {
                    result =  doNotForgetqueue[i].GetPercentageResult();
                    temp = doNotForgetqueue[i];
                };
            };
        };
    }

    return temp;
}

template <unsigned long int size>
unsigned long int ThreadIABoardQueue<size>::Size()
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    return numberOfElements;

}

template <unsigned long int size>
ThreadIABoardQueue<size>::~ThreadIABoardQueue()
{
    delete [] queue;
    delete [] doNotForgetqueue;
    //delete mutex;
}
