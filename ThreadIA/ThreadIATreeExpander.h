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

       void Expand(unsigned int howManySteps, unsigned int frequencyOfTransferData, ThreadIABoardQueue<MQueue> &mainBoardQueue, const unsigned short numThread, std::atomic<int> *percentSteps);
       void ExpandWithoutQueue(unsigned int howManySteps, unsigned int frequencyOfTransferData, const unsigned short numThread, std::atomic<int> *percentSteps);
       void SetMainBoardQueue(ThreadIABoardQueue<MQueue> * mainBoardQueue);
    private:
       void TransferBoards(ThreadIABoardQueue<MQueue> &mainBoardQueue);
       inline void AddToMainQueue(const Board &board);
       inline void AddToDoNotForgetQueue(const Board &board);
       bool ExpandWhite(Board board, unsigned int stepNumber = 1);
       bool ExpandBlack(Board board, unsigned int stepNumber = 1);

       bool trace;

       ThreadIABoardQueue<MQueue> * mainBoardQueue_2;
       const unsigned long int queueSize;       
       unsigned long int lastQueueElement;
       unsigned long int firstQueueElement;
       unsigned long int numberOfElements;
       Board queue[sQueue];

       const unsigned long int doNotForgetQueueSize;
       unsigned long int lastDoNotForgetQueueElement;
       Board doNotForgetQueue[sQueue/50];

       unsigned short threadNumber;              
};

#endif // THREADIATREEEXPANDER_H
