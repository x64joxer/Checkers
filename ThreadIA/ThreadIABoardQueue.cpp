#include "ThreadIA/ThreadIABoardQueue.h"

template <unsigned long int size>
ThreadIABoardQueue<size>::ThreadIABoardQueue()
{
    first = 0;
    last = 0;
    numberOfElements = 0;
    queue = new Board[size];
}

template <unsigned long int size>
void ThreadIABoardQueue<size>::Clear()
{
    first = 0;
    last = 0;
    numberOfElements = 0;
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::PopFront()
{
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
        return queue[temp];
    };

    Traces() << "\n" << "ERROR: No elements to get!";
    return Board();
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
    //TODO
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::GetBestResult()
{
    double result;
    Board temp;

    if (numberOfElements>0)
    {
        result = queue[first].GetPercentageResult();
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

    return temp;
}

template <unsigned long int size>
unsigned long int ThreadIABoardQueue<size>::Size()
{
    return numberOfElements;
}

template <unsigned long int size>
ThreadIABoardQueue<size>::~ThreadIABoardQueue()
{
    delete [] queue;
}
