#ifndef THREADIATREEEXPANDER_H
#define THREADIATREEEXPANDER_H

#include "Board.h"
#include "Traces/Traces.h"
#include "IA/IAPossibleMoves.h"
#include "ThreadIA/ThreadIABoardQueue.h"
#include "ProgramVariables.h"

enum KindOfSteps { Time, Step };

template <unsigned long long MQueue, unsigned long long sQueue>
class ThreadIATreeExpander
{
    public:
       ThreadIATreeExpander();       
       void Expand(unsigned long long howManySteps,
                   unsigned int frequencyOfTransferData,
                   ThreadIABoardQueue<MQueue> &mainBoardQueue,
                   const unsigned short numThread,
                   std::atomic<int> *percentSteps,
                   KindOfSteps stepKind);

       void ExpandWithoutQueue(unsigned int howManySteps, unsigned int frequencyOfTransferData, const unsigned short numThread, std::atomic<int> *percentSteps, KindOfSteps stepKind);
       void SetMainBoardQueue(ThreadIABoardQueue<MQueue> * mainBoardQueue);

    private:
       void TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue);
       inline void AddToMainQueue(const Board &board);
       inline void AddToDoNotForgetQueue(const Board &board);
       bool ExpandWhite(Board board, unsigned int stepNumber = 1);
       bool ExpandBlack(Board board, unsigned int stepNumber = 1);

       ThreadIABoardQueue<MQueue> * mainBoardQueue_2;
       const unsigned long long queueSize;       
       unsigned long long lastQueueElement;
       unsigned long long firstQueueElement;
       unsigned long long numberOfElements;
       Board queue[sQueue];

       const unsigned long long doNotForgetQueueSize;
       unsigned long long lastDoNotForgetQueueElement;
       Board doNotForgetQueue[sQueue/50];

       unsigned short threadNumber;              
};

#endif // THREADIATREEEXPANDER_H
