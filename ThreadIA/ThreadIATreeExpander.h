#ifndef THREADIATREEEXPANDER_H
#define THREADIATREEEXPANDER_H

#include "Board.h"
#include "Traces/Traces.h"
#include "IA/IAPossibleMoves.h"

class ThreadIATreeExpander
{
    public:
       ThreadIATreeExpander();

       void Expand(Board board, unsigned int howManySteps);
    private:
       bool ExpandWhite(Board board, unsigned int stepNumber = 1);
       bool ExpandBlack(Board board, unsigned int stepNumber = 1);

       bool trace;

       const unsigned long int queueSize;
       unsigned long int lastQueueElement;
       unsigned long int firstQueueElement;
       Board queue[5000];

       const unsigned long int doNotForgetQueueSize;
       unsigned long int lastDoNotForgetQueueElement;
       Board doNotForgetQueue[100];
};

#endif // THREADIATREEEXPANDER_H
