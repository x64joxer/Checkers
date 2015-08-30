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
        Traces() << "\n" << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Requesting white pawn not exist!";
    } else
    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
          Traces() << "\n" << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
         Traces() << "\n" << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (IsPawnOnPos(x,y))
    {
        Traces() << "\n" << "ERROR! SetWhitePawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on another pawn!";
    } else
    {        
        Pawn &ref = white.at(number);
        ref.x = x;
        ref.y = y;
        if (y == 7)
        {
            ref.pons = true;
        };
    };
}

void Board::SetBlackPawnPos(const unsigned short number,const unsigned short x,const unsigned short y)
{
    if (number>black.size()-1)
    {
        Traces() << "\n" << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Requesting black pawn not exist!";
    } else
    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
        Traces() << "\n" << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
        Traces() << "\n" << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on white field!";
    } else
    if (IsPawnOnPos(x,y))
    {
        Traces() << "\n" << "ERROR! SetBlackPawnPos(unsigned short number,unsigned short x, unsigned short y) Try to set pawn on another pawn!";
    } else
    {
        Pawn &ref = black.at(number);
        ref.x = x;
        ref.y = y;
        if (y == 0)
        {
            ref.pons = true;
        };
    };
}

void Board::PutWhiteTopLeftPawn(const unsigned short number)
{
    if (!GetWhitePawnPons(number))
    {
        Traces() << "\n" << "ERROR! Board::PutWhiteTopLeftPawn(const unsigned short number) Pawn is not pons!";
    } else
    {
        PawnPos tempPos = GetWhitePawnPos(number);
        SetWhitePawnPos(number, tempPos.X() -1, tempPos.Y()-1);
    };
}

void Board::PutWhiteTopRightPawn(const unsigned short number)
{
    if (!GetWhitePawnPons(number))
    {
        Traces() << "\n" << "ERROR! Board::PutWhiteTopRightPawn(const unsigned short number) Pawn is not pons!";
    } else
    {
        PawnPos tempPos = GetWhitePawnPos(number);
        SetWhitePawnPos(number, tempPos.X() +1, tempPos.Y()-1);
    };
}

void Board::PutWhiteBottomLeftPawn(const unsigned short number)
{
    PawnPos tempPos = GetWhitePawnPos(number);
    SetWhitePawnPos(number, tempPos.X() -1, tempPos.Y()+1);
}

void Board::PutWhiteBottomRightPawn(const unsigned short number)
{
    PawnPos tempPos = GetWhitePawnPos(number);
    SetWhitePawnPos(number, tempPos.X() +1, tempPos.Y()+1);
}

void Board::PutBlackTopLeftPawn(const unsigned short number)
{
        PawnPos tempPos = GetBlackPawnPos(number);
        SetBlackPawnPos(number, tempPos.X() -1, tempPos.Y()-1);
}

void Board::PutBlackTopRightPawn(const unsigned short number)
{
        PawnPos tempPos = GetBlackPawnPos(number);
        SetBlackPawnPos(number, tempPos.X() +1, tempPos.Y()-1);
}

void Board::PutBlackBottomLeftPawn(const unsigned short number)
{
    if (!GetBlackPawnPons(number))
    {
        Traces() << "\n" << "ERROR! Board::PutBlackBottomLeftPawn(const unsigned short number) Pawn is not pons!";
    } else
    {
        PawnPos tempPos = GetBlackPawnPos(number);
        SetBlackPawnPos(number, tempPos.X() -1, tempPos.Y()+1);
    };
}

void Board::PutBlackBottomRightPawn(const unsigned short number)
{
    if (!GetBlackPawnPons(number))
    {
        Traces() << "\n" << "ERROR! Board::PutBlackBottomRightPawn(const unsigned short number) Pawn is not pons!";
    } else
    {
        PawnPos tempPos = GetBlackPawnPos(number);
        SetBlackPawnPos(number, tempPos.X() +1, tempPos.Y()+1);
    };
}

void Board::RemoveBlackPawn(const unsigned short number)
{
    if (number>black.size()-1)
    {
        Traces() << "\n" << "ERROR! Board::RemoveBlackPawn(const unsigned short number) Requesting white pawn not exist!";
    };

    black.erase(black.begin()+number);
}

void Board::RemoveWhitePawn(const unsigned short number)
{
    if (number>white.size()-1)
    {
        Traces() << "\n" << "ERROR! Board::RemoveWhitePawn(const unsigned short number) Requesting white pawn not exist!";
    };

    white.erase(white.begin()+number);
}

PawnPos Board::GetWhitePawnPos(const unsigned short number)
{
    if (number>white.size()-1)
    {
        Traces() << "\n" << "ERROR! GetWhitePawnPos(const unsigned short number) Requesting white pawn not exist!";
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
        Traces() << "\n" << "ERROR! GetBlackPawnPos(const unsigned short number) Requesting black pawn not exist!";
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
        Traces() << "\n" << "ERROR! GetWhitePawnPons(const unsigned short number) Requesting white pawn not exist!";
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

    Traces() << "\n" << "ERROR! Board::GetWhitePawnNumber(const unsigned short x, const unsigned short y) Requesting White pawn not exist!";

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

    Traces() << "\n" << "ERROR! Board::GetBlackPawnNumber(const unsigned short x, const unsigned short y) Requesting black pawn not exist!";

    return 0;
}

bool Board::GetBlackPawnPons(const unsigned short number)
{
    if (number>black.size()-1)
    {        
        Traces() << "\n" << "ERROR! GetBlackPawnPons(const unsigned short number) Requesting black pawn not exist!";
    } else
    {
        Pawn temp = black.at(number);
        return temp.pons;
    };
    return 0;
}

bool Board::SetWhitePawnPons(const unsigned short number, const bool flag)
{
    if (number>white.size()-1)
    {
        Traces() << "\n" << "ERROR! Board::SetWhitePawnPons(const unsigned short number, const bool flag) Requesting white pawn not exist!";
    } else
    {
        Pawn &ref = white.at(number);
        ref.pons = flag;
    };
}

bool Board::SetBlackPawnPons(const unsigned short number, const bool flag)
{
    if (number>black.size()-1)
    {
        Traces() << "\n" << "ERROR! Board::SetWhitePawnPons(const unsigned short number, const bool flag) Requesting white pawn not exist!";
    } else
    {
        Pawn &ref = black.at(number);
        ref.pons = flag;
    };
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

void Board::RemovePawnFrom(const unsigned short x, const unsigned short y)
{

    if (((y+1) % 2 == 1)&&((x+1) % 2 == 1))
    {
        Traces() << "\n" << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Try to set pawn on white field!";
    } else
    if (((y+1) % 2 == 0)&&((x+1) % 2 == 0))
    {
        Traces() << "\n" << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Try to set pawn on white field!";
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

    if (!flag) Traces() << "\n" << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Requesting pawn that not exist!";
}

unsigned short Board::GetResult()
{
    unsigned short result;

    result = white.size();
    result+= -(black.size() - 12);

    return result;
}

double Board::GetPercentageResult()
{
    Traces() << "\n" << "LOG: Board::GetPercentageResult() = " << (double)black.size() / (double)white.size();
    return (double)black.size() / (double)white.size();
}

void Board::printDebug()
{
    QString line;
    bool flag = 0;
    Traces() << "\n" << "LOG: White= " << GetNumberOfWhite();
    Traces() << "\n" << "LOG: Black= " << GetNumberOfBlack();

    for (int y=0; y<8; y++)
    {

        line ="|";

        for (int x=0; x<8; x++)
        {

            if (IsWhitePawnOnPos(x,y))
            {
                unsigned short number = GetWhitePawnNumber(x,y);
                if (GetWhitePawnPons(number))
                {
                    line += "W";
                } else
                {
                    line += "w";
                };
            } else
            if (IsBlackPawnOnPos(x,y))
            {
                unsigned short number = GetBlackPawnNumber(x,y);
                if (GetBlackPawnPons(number))
                {
                    line += "B";
                } else
                {
                    line += "b";
                };
            } else
            if (flag)
            {
                line+="\\";
            }
            else
            {
                line+=" ";
            };

            line+="|";
            flag = !flag;
        };

        Traces() << "\n" << line;
        flag = !flag;
    };
}

Board & Board::operator =(char* data)
{

    //| |w| |w| |w| |w|
    //|w| |w| |w| |w| |
    //| |w| |w| |w| |w|
    //|\| |\| |\| |\| |
    //| |\| |\| |\| |b|
    //|b| |b| |b| |\| |
    //| |b| |b| |b| |b|
    //|b| |b| |b| |b| |
    numberOfBlack = 0;
    numberOfBlack = 0;
    white.clear();
    black.clear();

    for (int y=0;y<8;y++)
    {
        int realPositionX;
        if ((y+1)%2 == 1)
        {
            realPositionX = 0;
        } else
        {
            realPositionX = 0;
        };

        for (int x=0;x<17;x++)
        {
           int position = (y*17)+x;

           if (data[position] == 'w')
           {
             white.push_back(Pawn(realPositionX,y,0,0));
             realPositionX += 1;
           } else
           if (data[position] == 'W')
           {
             white.push_back(Pawn(realPositionX,y,0,1));

             realPositionX += 1;
           } else
           if (data[position] == 'b')
           {
             black.push_back(Pawn(realPositionX,y,0,0));
qDebug() << realPositionX << " " << y;
             realPositionX += 1;
           } else
           if (data[position] == 'B')
           {
             black.push_back(Pawn(realPositionX,y,0,1));

             realPositionX += 1;
           }else
           if (data[position] == ' ')
           {
               realPositionX += 1;
           } else
           if (data[position] == '\\')
           {
               realPositionX += 1;
           };

        };
    };
}


Board & Board::operator =(std::string data)
{

    //| |w| |w| |w| |w|
    //|w| |w| |w| |w| |
    //| |w| |w| |w| |w|
    //|\| |\| |\| |\| |
    //| |\| |\| |\| |b|
    //|b| |b| |b| |\| |
    //| |b| |b| |b| |b|
    //|b| |b| |b| |b| |
    numberOfBlack = 0;
    numberOfBlack = 0;
    white.clear();
    black.clear();

    for (int y=0;y<8;y++)
    {
        int realPositionX;
        if ((y+1)%2 == 1)
        {
            realPositionX = 0;
        } else
        {
            realPositionX = 0;
        };

        for (int x=0;x<17;x++)
        {
           int position = (y*17)+x;

           if (data[position] == 'w')
           {
             white.push_back(Pawn(realPositionX,y,0,0));
             realPositionX += 1;
           } else
           if (data[position] == 'W')
           {
             white.push_back(Pawn(realPositionX,y,0,1));

             realPositionX += 1;
           } else
           if (data[position] == 'b')
           {
             black.push_back(Pawn(realPositionX,y,0,0));
qDebug() << realPositionX << " " << y;
             realPositionX += 1;
           } else
           if (data[position] == 'B')
           {
             black.push_back(Pawn(realPositionX,y,0,1));

             realPositionX += 1;
           }else
           if (data[position] == ' ')
           {
               realPositionX += 1;
           } else
           if (data[position] == '\\')
           {
               realPositionX += 1;
           };

        };
    };
}

bool Board::operator ==(Board data)
{
    Traces() << "\n" << "Board::operator ==(Board data)";
    if (GetNumberOfBlack()!=data.GetNumberOfBlack())
    {
      return false;
    };
    if (GetNumberOfWhite()!=data.GetNumberOfWhite())
    {
      return false;
    };

    if (GetNumberOfWhite()>0)
    {
        for (unsigned short int i=0;i<GetNumberOfWhite();i++)
        {
            if (GetWhitePawnPos(i) != data.GetWhitePawnPos(i))
            {
                return 0;
            };

            if (GetWhitePawnPons(i)!=data.GetWhitePawnPons(i))
            {
              return 0;
            };
        };
    };

    if (GetNumberOfBlack()>0)
    {
        for (unsigned short int i=0;i<GetNumberOfBlack();i++)
        {
            if (GetBlackPawnPos(i) != data.GetBlackPawnPos(i))
            {
                return 0;
            };

            if (GetBlackPawnPons(i) != data.GetBlackPawnPons(i))
            {
              return 0;
            };
        };
    };

    return 1;
}
