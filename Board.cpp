#include "Board.h"

Board::Board()
{
    Clear();
}


void Board::Clear()
{
    bool flag = 0;
    numberOfBlack = 8;
    numberOfWhite = 8;
    white.clear();
    black.clear();

    Pawn temp;
    for (int y = 0;y<3;y++)
    {
        for (int x = 0;x<8;x++)
        {
            if (flag)
            {
                white.push_back(Pawn(x,y,0,0));
                temp = white.at(white.size()-1);
            };
            flag = !flag;
        };
        flag = !flag;
    };

    for (int y = 5;y<8;y++)
    {
        for (int x = 0;x<8;x++)
        {
            if (flag)
            {
                black.push_back(Pawn(x,y,0,0));
            };
            flag = !flag;
        };
        flag = !flag;
    };
}

void Board::SetWhitePawnPos(const unsigned short number,const unsigned short x,const unsigned short y)
{
    if (number>white.size()-1)
    {
        qDebug() << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Requesting white pawn not exist!";
    } else
    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
          qDebug() << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
         qDebug() << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (IsPawnOnPos(x,y))
    {
        qDebug() << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on another pawn!";
    } else
    {
        Pawn &ref = white.at(number);
        ref.x = x;
        ref.y = y;
    };
}

void Board::SetBlackPawnPos(const unsigned short number,const unsigned short x,const unsigned short y)
{
    if (number>black.size()-1)
    {
        qDebug() << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Requesting black pawn not exist!";
    } else
    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
        qDebug() << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
        qDebug() << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (IsPawnOnPos(x,y))
    {
        qDebug() << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on another pawn!";
    } else
    {
        Pawn &ref = black.at(number);
        ref.x = x;
        ref.y = y;
    };
}

void Board::RemoveBlackPawn(const unsigned short number)
{
    if (number>black.size()-1)
    {
        qDebug() << "ERROR! Board::RemoveBlackPawn(const unsigned short number) Requesting white pawn not exist!";
    };

    white.erase(black.begin()+number);
}

void Board::RemoveWhitePawn(const unsigned short number)
{
    if (number>white.size()-1)
    {
        qDebug() << "ERROR! Board::RemoveWhitePawn(const unsigned short number) Requesting white pawn not exist!";
    };

    white.erase(white.begin()+number);
}

PawnPos Board::GetWhitePawnPos(const unsigned short number)
{
    if (number>white.size()-1)
    {
        qDebug() << "ERROR! GetWhitePawnPos(const unsigned short number) Requesting white pawn not exist!";
    } else        
    {
        Pawn temp = white.at(number);
        return PawnPos(temp.x, temp.y);
    };
    return PawnPos(0,0);
}

PawnPos Board::GetBlackPawnPos(const unsigned short number)
{
    if (number>black.size()-1)
    {        
        qDebug() << "ERROR! GetBlackPawnPos(const unsigned short number) Requesting black pawn not exist!";
    } else
    {
        Pawn temp = black.at(number);
        return PawnPos(temp.x, temp.y);
    };
    return PawnPos(0,0);
}

bool Board::GetWhitePawnPons(const unsigned short number)
{
    if (number>white.size()-1)
    {
        qDebug() << "ERROR! GetWhitePawnPons(const unsigned short number) Requesting white pawn not exist!";
    } else
    {
        Pawn temp = white.at(number);
        return temp.pons;
    };
    return 0;
}

unsigned short Board::GetWhitePawnNumber(const unsigned short x, const unsigned short y)
{
    PawnPos temp;
    for (int i =0;i<GetNumberOfWhite();i++)
    {
       temp = GetWhitePawnPos(i);
       if ((temp.X() == x)&&(temp.Y() == y))
       {
            return i;
       };
    };

    qDebug() << "ERROR! Board::GetWhitePawnNumber(const unsigned short x, const unsigned short y) Requesting White pawn not exist!";

    return 0;
}

unsigned short Board::GetBlackPawnNumber(const unsigned short x, const unsigned short y)
{
    PawnPos temp;
    for (int i =0;i<GetNumberOfBlack();i++)
    {
       temp = GetBlackPawnPos(i);
       if ((temp.X() == x)&&(temp.Y() == y))
       {
            return i;
       };
    };

    qDebug() << "ERROR! Board::GetBlackPawnNumber(const unsigned short x, const unsigned short y) Requesting black pawn not exist!";

    return 0;
}

bool Board::GetBlackPawnPons(const unsigned short number)
{
    if (number>black.size()-1)
    {        
        qDebug() << "ERROR! GetBlackPawnPons(const unsigned short number) Requesting black pawn not exist!";
    } else
    {
        Pawn temp = black.at(number);
        return temp.pons;
    };
    return 0;
}

bool Board::IsPawnOnPos(const unsigned short x, const unsigned short y)
{
    foreach(Pawn temp, white)
    {
        if ((temp.x == x)&&(temp.y == y))
        {
            return 1;
        };
    };

    foreach(Pawn temp, black)
    {
        if ((temp.x == x)&&(temp.y == y))
        {
            return 1;
        };
    };

    return 0;
}

bool Board::IsWhitePawnOnPos(const unsigned short x, const unsigned short y)
{
    foreach(Pawn temp, white)
    {
        if ((temp.x == x)&&(temp.y == y))
        {
            return 1;
        };
    };

    return 0;
}

bool Board::IsBlackPawnOnPos(const unsigned short x, const unsigned short y)
{
    foreach(Pawn temp, black)
    {
        if ((temp.x == x)&&(temp.y == y))
        {
            return 1;
        };
    };

    return 0;
}

unsigned short Board::GetNumberOfWhite()
{
   return white.size();
}

unsigned short Board::GetNumberOfBlack()
{
    return black.size();
}

void Board::RemovePonsFrom(const unsigned short x, const unsigned short y)
{

    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
        qDebug() << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
        qDebug() << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Try to set pawn on white field!";
    };

    unsigned short counter = 0;
    bool flag = 0;

    foreach(Pawn temp, white)
   {
        if ((temp.x == x)&&(temp.y == y))
        {            
            white.erase(white.begin()+counter);
            numberOfWhite--;
            flag = 1;
        };
        counter ++;
    };

    counter = 0;
    foreach(Pawn temp, black)
    {
        if ((temp.x == x)&&(temp.y == y))
        {            
            black.erase(black.begin()+counter);
            numberOfBlack--;
            flag = 1;
        };
        counter ++;
    };

    if (!flag) qDebug() << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Requesting pawn that not exist!";
}
