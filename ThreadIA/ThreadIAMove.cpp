#include "ThreadIA/ThreadIAMove.h"

template  <unsigned long int QMain>
ThreadIAMove<QMain>::ThreadIAMove()
{

}

template  <unsigned long int QMain>
void ThreadIAMove<QMain>::operator ()(Board * boardWsk, std::atomic_bool * flag, std::atomic<int> *percentSteps, const unsigned short numberOfThreads, const unsigned int refreshMainQueue, const unsigned int numberOfStepsToDo, KindOfSteps stepKind)
{
    const unsigned short maxThreads = numberOfThreads + 1;
    std::thread iaThread[maxThreads];
    ThreadIATreeExpander<QMain,5000> expander[maxThreads];
    unsigned int numberOfSteps = numberOfStepsToDo / numberOfThreads;    

    if (stepKind == KindOfSteps::Time)
    {
        numberOfSteps = numberOfStepsToDo;
    };

    //Create first elements
    Board temp = *boardWsk;
    temp.StartWhite();
    temp.SetWhitePatchEnd(false);

    queue.PushBack(temp);
    CreateFirstElements();    

    //When all black killed
    if (queue.First().GetNumberOfBlack() == 0)
    {
        *boardWsk = queue.First();
        *flag = true;
    } else
    //Can not move or all black killed    
    if (queue.Size() == 0)
    {
        *flag = true;
    } else
    {
        //Set origin to all
        SetOriginToAll();

        //Start threads
        for (unsigned short i=1;i<=numberOfThreads;i++)
        {
            expander[i].SetMainBoardQueue(&queue);
            iaThread[i] = std::move(std::thread(&ThreadIATreeExpander<QMain,5000>::ExpandWithoutQueue,
                                                &expander[i],
                                                numberOfSteps,
                                                refreshMainQueue,
                                                i,
                                                percentSteps,
                                                stepKind
                                                ));

        };

        for (unsigned short i=1;i<=numberOfThreads;i++)
        {
            iaThread[i].join();
        };

        qDebug() << "Num of elements" << queue.Size();

        if (numberOfThreads <2)
        {
            temp = queue.GetBestResult();
        } else
        {
        //NEW METHOD
        //qDebug() << "New method";
        unsigned int minElements = 2000;
        unsigned short numOfThreads = numberOfThreads;

        if (queue.Size() / minElements >= queue.SizeDoNotForget() / minElements)
        {
            if (queue.Size() / minElements < numOfThreads) numOfThreads = queue.Size() / minElements;
        } else
        {
            if (queue.SizeDoNotForget() / minElements < numOfThreads) numOfThreads = queue.SizeDoNotForget() / minElements;
        };
        if (numOfThreads == 0) numOfThreads = 1;
        //qDebug() << "numOfThreads = " << numOfThreads;

        unsigned int firstQueueElelemtsOnThread = queue.Size() / numberOfThreads;
        unsigned int secondQueueElelemtsOnThread = queue.SizeDoNotForget() / numberOfThreads;

        if (firstQueueElelemtsOnThread == 0)
        {
            if (queue.Size()>0) firstQueueElelemtsOnThread = queue.Size()-1;
        };
        if (secondQueueElelemtsOnThread == 0) secondQueueElelemtsOnThread = queue.SizeDoNotForget();

        unsigned int start = queue.GetFirstNumber();
        unsigned int start2 = 0;
        unsigned int stop = firstQueueElelemtsOnThread;
        unsigned int stop2 = secondQueueElelemtsOnThread;
        bool flag1 = true;
        bool flag2 = true;
        Board best[numOfThreads];

        for (unsigned short i=1;i<=numOfThreads;i++)
        {
            Traces() << "\n" << "LOG: Start sharing for thread " << i;
            if (firstQueueElelemtsOnThread ==0) flag1 = false;
            if (secondQueueElelemtsOnThread == 0) flag2 = false;
            if (firstQueueElelemtsOnThread >= queue.GetFirstNumber()+ queue.Size()) firstQueueElelemtsOnThread = (queue.GetFirstNumber()+ queue.Size())-1;
            if (secondQueueElelemtsOnThread >= queue.SizeDoNotForget()) secondQueueElelemtsOnThread = queue.SizeDoNotForget() -1;
            stop = start + firstQueueElelemtsOnThread;
            stop2 = start2 + secondQueueElelemtsOnThread;
            //qDebug() << "start=" << start;
            //qDebug() << "stop=" << stop;
            //qDebug() << "start2=" << start2;
            //qDebug() << "stop2=" << stop2;
            //qDebug() << "flag1=" << flag1;
            //qDebug() << "flag2=" << flag2;

            //qDebug() << "iaThread[i] = std::move(std::thread(...";
            iaThread[i] = std::move(std::thread(&ThreadIABoardQueue<QMain>::GetBestResult2,
                                                &queue,
                                                flag1,
                                                start,
                                                stop,
                                                flag2,
                                                start2,
                                                stop2,
                                                &best[i-1]
                                                ));
            start = stop;
            start2 = stop2;
        }

        Traces() << "\n" << "LOG: Waiting for all threads...";

        for (unsigned short i=1;i<=numOfThreads;i++)
        {
            Traces() << "\n" << "LOG: Waiting for " << i;
            iaThread[i].join();
            Traces() << "\n" << "LOG: Thread " << i << " finished";
        };

        Traces() << "\n" << "LOG: Workers finished";
        temp = best[0];
        for (unsigned short i=0;i<numOfThreads;i++)
        {
            if (temp.GetPercentageResult()>best[i].GetPercentageResult())
            {
                temp = best[i];
            };
        };
        };
        //END

        queue.Clear();
        *boardWsk = temp.GetOrigin();

        Traces() << "\n" << "LOG: Best board set:";
        temp.printDebug();
        boardWsk->printDebug();


        *flag = true;        
    };
   Traces::RemoveThreadID();
}

template  <unsigned long int QMain>
void ThreadIAMove<QMain>::CreateFirstElements()
{
    Traces() << "\n" << "LOG: void ThreadIAMove<QMain>::CreateFirstElements()";
    ThreadIATreeExpander<QMain,100> expander;
    expander.Expand(1,100,queue,0, NULL, KindOfSteps::Step);
}

template  <unsigned long int QMain>
void ThreadIAMove<QMain>::SetOriginToAll()
{
    Traces() << "\n" << "LOG: void ThreadIAMove<QMain>::SetOriginToAll()";
    unsigned long int size = queue.Size();
    Board temp;

    if (size>0)
    {
        for (unsigned int i=0;i<size;i++)
        {
            temp = queue.PopFront(0);
            temp.SetOrigin(temp);          

            Traces() << "\n" << "LOG: Origin set";
            temp.printDebug();
            queue.PushBack(temp);
        }
    };
}
