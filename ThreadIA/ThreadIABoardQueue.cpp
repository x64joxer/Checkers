#include "ThreadIA/ThreadIABoardQueue.h"

template <unsigned long int size>
ThreadIABoardQueue<size>::ThreadIABoardQueue():
                          first(0),
                          last(0),
                          numberOfElements(0),
                          workersFlags(0),
                          doNotForgetnumberOfElements(0)
{
    queue = new Board[size];
    doNotForgetqueue = new Board[size];
}

template <unsigned long int size>
void ThreadIABoardQueue<size>::Clear()
{
    first = 0;
    last = 0;
    numberOfElements = 0;
    doNotForgetnumberOfElements =0;    
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::First()
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    return queue[first];
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::PopFront(const unsigned short num)
{    
    Traces() << "\n" << "LOG: Board ThreadIABoardQueue<size>::PopFront()";    
    {
        std::lock_guard<std::mutex> guard(mutex_guard);
        SetWorkerFlag(false, num);
    }

    std::unique_lock<std::mutex> guard(mutex_guard);
    condition_var.wait(guard,[this]
    {
        return (!Empty()) | (!workersFlags) ;}
    );

    if (num>0)
    {
            if (numberOfElements>0)
            {
                SetWorkerFlag(true, num);
            } else
            if (!workersFlags)
            {
                Traces() << "\n" << "LOG: No active workers! Finishing!";                
                Board temp_null;
                temp_null.SetNullBoard(true);
                return temp_null;
            };
    };

    unsigned long int temp = first;    

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
        guard.unlock();
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
    std::lock_guard<std::mutex> guard(mutex_guard);
    Traces() << "\n" << "LOG: void ThreadIABoardQueue<size>::PushBack(Board board) Number of cells";

    if (numberOfElements == 0)
    {
       numberOfElements++;
       queue[last] = board;

       Traces() << "\n" << "LOG: first " << first;
       Traces() << "\n" << "LOG: last " << last;
       Traces() << "\n" << "LOG: Number of cells " << numberOfElements;
    } else
    if (numberOfElements<size)
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

    condition_var.notify_all();
}

template <unsigned long int size>
inline void ThreadIABoardQueue<size>::PushBackDoNotForget(Board &board)
{
    Traces() << "\n" << "LOG: inline void ThreadIABoardQueue<size>::PushBackDoNotForget(Board &board)";
    mutex_guard.lock();
    doNotForgetqueue[doNotForgetnumberOfElements] = board;
    ++doNotForgetnumberOfElements;
    mutex_guard.unlock();
    condition_var.notify_all();
}

template <unsigned long int size>
Board ThreadIABoardQueue<size>::GetBestResult()
{
    double result = 0;
    Board temp;

    qDebug() << "Number of eleents" << numberOfElements;
    qDebug() << "Number of do not forget eleents" << doNotForgetnumberOfElements;

    if (numberOfElements>0)
    {
        result = queue[first].GetPercentageResult();
        temp = queue[first];
        PopFront(0);

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
        if (result == 0)
        {
            result = doNotForgetqueue[0].GetPercentageResult();
            temp = doNotForgetqueue[0];
        };

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
void ThreadIABoardQueue<size>::GetBestResult2(bool make, const unsigned int start, const unsigned int stop, bool make2, const unsigned int start2, const unsigned int stop2, Board *best)
{
    Traces() << "\n" << "LOG: void ThreadIABoardQueue<size>::GetBestResult2";
    double result = 0;
    Board temp;

    Traces() << "\n" << "LOG: Number of eleents =" << numberOfElements;
    Traces() << "\n" << "LOG: Number of do not forget eleents =" << doNotForgetnumberOfElements;


    if (make)
    {
        Traces() << "\n" << "LOG: make = true";
        Traces() << "\n" << "LOG: start =" << start;
        Traces() << "\n" << "LOG: stop =" << stop;

        result = queue[start].GetPercentageResult();
        temp = queue[start];

        Traces() << "\n" << "LOG: Current best result";
        temp.printDebug();

        for (int i = start; i<stop; i++)
        {
            if (result>queue[i].GetPercentageResult())
            {
                result =  queue[i].GetPercentageResult();
                temp = queue[i];
                Traces() << "\n" << "LOG: New best result";
                temp.printDebug();
            };
        };
    };

    if (make2)
    {
        Traces() << "\n" << "LOG: make2 == true";
        Traces() << "\n" << "LOG: start2 =" << start2;
        Traces() << "\n" << "LOG: stop2 =" << stop2;

        if (!make)
        {
            Traces() << "\n" << "LOG: !make = false";
            result = doNotForgetqueue[start2].GetPercentageResult();
            temp = doNotForgetqueue[start2];            

            Traces() << "\n" << "LOG: Current best result";
            temp.printDebug();
        };

        Traces() << "\n" << "LOG: Searching best";

        for (int i = start2; i<stop2; i++)
        {
            if (result>doNotForgetqueue[i].GetPercentageResult())
            {
                result =  doNotForgetqueue[i].GetPercentageResult();
                temp = doNotForgetqueue[i];
                Traces() << "\n" << "LOG: New best result";
                temp.printDebug();
            };
        };
    };

    Traces() << "\n" << "LOG: End of searching";
    *best = temp;
}

template <unsigned long int size>
unsigned long int ThreadIABoardQueue<size>::Size()
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    return numberOfElements;

}

template <unsigned long int size>
unsigned long int ThreadIABoardQueue<size>::SizeDoNotForget()
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    return doNotForgetnumberOfElements;

}

template <unsigned long int size>
void ThreadIABoardQueue<size>::NotifyRest()
{
    condition_var.notify_all();
}

template <unsigned long int size>
unsigned long int ThreadIABoardQueue<size>::GetFirstNumber()
{
    return first;
}

template <unsigned long int size>
ThreadIABoardQueue<size>::~ThreadIABoardQueue()
{
    delete [] queue;
    delete [] doNotForgetqueue;
}

template <unsigned long int size>
void ThreadIABoardQueue<size>::SetWorkerFlag(const bool flag,const unsigned short number)
{
    if (number>0)
    {
        unsigned short val;

        if (!flag)
        {
            val = 65535;
            val-= pow(2, number);
            workersFlags = workersFlags & val;
        } else
        {
            val = pow(2, number);
            workersFlags = workersFlags | val;
        };
    };
}
