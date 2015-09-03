#include "ThreadIA/ThreadIABoardQueue.h"

template <unsigned long int size>
ThreadIABoardQueue<size>::ThreadIABoardQueue()
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
