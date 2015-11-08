#ifndef THREADIAMOVE_H
#define THREADIAMOVE_H

#include <atomic>
#include "Board.h"
#include "ThreadIA/ThreadIABoardQueue.h"
#include "ThreadIA/ThreadIABoardQueue.cpp"
#include "ThreadIA/ThreadIATreeExpander.cpp"
#include "TCP/MessageHandler.h"

template <unsigned long int QMain>
class ThreadIAMove
{
    public:
        ThreadIAMove();
        void SetMessageHandler(MessageHandler *wsk);

        void operator ()(Board * boardWsk,
                         std::atomic_bool * flag,
                         std::atomic<int> *percentSteps,
                         const unsigned short numberOfThreads,
                         const unsigned int refreshMainQueue,
                         const unsigned int numberOfStepsToDo,
                         KindOfSteps stepKind);

   private:
        ThreadIABoardQueue<QMain> queue;
        void CreateFirstElements();
        void SetOriginToAll();

        MessageHandler *messageHandler;

};

#endif // THREADIAMOVE_H
