#include "IADecisionTree.h"


IADecisionTree::IADecisionTree()
{
    previous = nullptr;
    numberOfElelments++;
    Traces() << "\n" << "LOG! IADecisionTree::IADecisionTree() Number of elements = " << numberOfElelments ;
}

bool IADecisionTree::Black()
{
    return !blackWhite;
}

bool IADecisionTree::White()
{
    return blackWhite;
}

Board IADecisionTree::GetOldestAncestor(IADecisionTree *wsk)
{
    IADecisionTree *temp;
    std::list<IADecisionTree *> white;

    Traces() << "\n" << "LOG! IADecisionTree::GetOldestAncestor(IADecisionTree *wsk)";

    if (wsk->GetPreviousElement() == nullptr)
    {
        Traces() << "\n" << "LOG! (wsk->GetPreviousElement() == nullptr)";
        return wsk->GetBoard();
    } else
    {
        while (wsk->GetPreviousElement() != nullptr)
        {
                temp = wsk;
                if (temp->Black())
                {
                  Traces() << "\n" << "LOG! Add to white list!";
                  temp->GetBoard().printDebug();
                  white.push_front(temp);
                } else
                {
                  //Traces() << "\n" << "LOG! Clear white list!";
                  //wsk->GetBoard().printDebug();
                  //white.clear();
                };
                wsk = wsk->GetPreviousElement();
        };
    };

    if (white.size()==0) white.push_front(temp);

    Traces() << "\n" << "LOG! Number of white steps =" << white.size();
    std::list<IADecisionTree *>::iterator iter = white.begin();
    temp = iter.operator *();
    if (white.size() == 0) Traces() << "\n" << "ERROR! White list is empty!";
    temp->GetBoard().printDebug();

    return temp->GetBoard();
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
    if ((number>=0)&&(number<=12))
    {
        previousMurder = number;
    } else
    {
        Traces() << "\n" << "ERROR! IADecisionTree::SetPreviousMurder(const unsigned short number) Out of range 0-12! Trying to set " << number;
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
    Traces() << "\n" << "LOG! IADecisionTree::~IADecisionTree() Number of elements = " << numberOfElelments ;
}

bool IADecisionTree::IsSimilarBlackInPatch(IADecisionTree *wsk, Board board)
{
    unsigned short int counter = 0;
    IADecisionTree *temp;

    Traces() << "\n" << "LOG! IADecisionTree::GetOldestAncestor(IADecisionTree *wsk)";

    while (wsk->GetPreviousElement() != nullptr)
    {
            temp = wsk;
            if (temp->Black())
            {
                if (temp->GetBoard() == board) return true;
            };
            wsk = wsk->GetPreviousElement();

            counter++;

            if (counter==12) break;
    };

    temp = wsk;
    if (temp->Black())
    {
        if (temp->GetBoard() == board) return true;
    };

    return false;
}


bool IADecisionTree::IsSimilarWhiteInPatch(IADecisionTree *wsk, Board board)
{
    unsigned short int counter = 0;
    IADecisionTree *temp;

    Traces() << "\n" << "LOG! IADecisionTree::GetOldestAncestor(IADecisionTree *wsk)";

    while (wsk->GetPreviousElement() != nullptr)
    {
            temp = wsk;
            if (temp->White())
            {
                if (temp->GetBoard() == board) return true;
            };
            wsk = wsk->GetPreviousElement();

            counter++;

            if (counter==12) break;
    };

    temp = wsk;
    if (temp->White())
    {
        if (temp->GetBoard() == board) return true;
    };

    return false;
}

unsigned int IADecisionTree::numberOfElelments = 0;
