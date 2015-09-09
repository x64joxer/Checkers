#ifndef THREADIATREEEXPANDER_H
#define THREADIATREEEXPANDER_H

#include "Board.h"
#include "Traces/Traces.h"
#include "IA/IAPossibleMoves.h"
#include "ThreadIA/ThreadIABoardQueue.h"

template <unsigned long int MQueue, unsigned long int sQueue>
class ThreadIATreeExpander
{
    public:
       ThreadIATreeExpander();

       void Expand(unsigned int howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue, const unsigned short numThread);
       void ExpandWithoutQueue(unsigned int howManySteps, unsigned int frequencyOfTransferData, const unsigned short numThread);       
       ThreadIABoardQueue<MQueue> * mainBoardQueue_2;
    private:
       void TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue);
       bool ExpandWhite(Board board, unsigned int stepNumber = 1);
       bool ExpandBlack(Board board, unsigned int stepNumber = 1);

       bool trace;

       const unsigned long int queueSize;       
       unsigned long int lastQueueElement;
       unsigned long int firstQueueElement;
       Board queue[sQueue];

       const unsigned long int doNotForgetQueueSize;
       unsigned long int lastDoNotForgetQueueElement;
       Board doNotForgetQueue[sQueue/50];

       unsigned short threadNumber;              
};

#endif // THREADIATREEEXPANDER_H
