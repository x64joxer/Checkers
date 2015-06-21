#include "IADecisionTree.h"


IADecisionTree::IADecisionTree()
{
    previous = NULL;
    numberOfElelments++;
    qDebug() << "LOG! IADecisionTree::IADecisionTree() Number of elements = " << numberOfElelments ;
}

bool IADecisionTree::Black()
{
    return !blackWhite;
}

bool IADecisionTree::White()
{
    return blackWhite;
}

void IADecisionTree::SetBoard(Board &b)
{
    board = b;
}

void IADecisionTree::SetPreviousElement(IADecisionTree *wsk)
{
    previous = wsk;
}

IADecisionTree * IADecisionTree::GetPreviousElement()
{
    return previous;
}

void IADecisionTree::StartBlack()
{
    blackWhite = 0;
}

void IADecisionTree::StartWhite()
{
    blackWhite = 1;
}

Board IADecisionTree::GetBoard()
{
    return board;
}

IADecisionTree * IADecisionTree::AddNextStep(Board b,const bool blackWhte, const unsigned short number)
{
    //Mutex
    IADecisionTree *wsk = new IADecisionTree();

    wsk->SetPreviousMurder(number);
    if (blackWhte)
    {
        wsk->StartWhite();
    } else
    {
        wsk->StartBlack();
    };
    wsk->SetBoard(b);

    wsk->SetPreviousElement(this);
    next.push_back(wsk);

    return wsk;
    //Mutex
}

void IADecisionTree::SetPreviousMurder(const unsigned short number)
{
    if ((number>=0)&&(number<=9))
    {
        previousMurder = number;
    } else
    {
        qDebug() << "ERROR! IADecisionTree::SetPreviousMurder(const unsigned short number) Out of range 0-9!" ;
    };
}

unsigned short IADecisionTree::GetPreviousMurder()
{
    return previousMurder;
}

IADecisionTree::~IADecisionTree()
{
    foreach (IADecisionTree *wsk, next)
    {
        delete wsk;
    }
    next.clear();
    numberOfElelments--;
   // qDebug() << "LOG! IADecisionTree::~IADecisionTree() Number of elements = " << numberOfElelments ;
}

unsigned int IADecisionTree::numberOfElelments = 0;
