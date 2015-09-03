#include "Board.h"

Board::Board()
{
    Clear();
}

void Board::Clear()
{
    bool flag = 0;

    unsigned short counter =0;
    for (int y = 0;y<3;y++)
    {
        for (int x = 0;x<8;x++)
        {
            if (flag)
            {
                white[counter] = Pawn(x,y,0,0);
                counter++;
            };
            flag = !flag;
        };
        flag = !flag;
    };

    counter =0;
    for (int y = 5;y<8;y++)
    {
        for (int x = 0;x<8;x++)
        {
            if (flag)
            {
                black[counter] = Pawn(x,y,0,0);
                counter++;
            };
            flag = !flag;
        };
        flag = !flag;
    };
}

void Board::SetWhitePawnPos(const unsigned short number,const unsigned short x,const unsigned short y)
{
    if (number>numberOfWhite()-1)
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
        Pawn &ref = white[number];
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
    if (number>numberOfBlack()-1)
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
        Pawn &ref = black[number];
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
    if (number>numberOfBlack()-1)
    {
        Traces() << "\n" << "ERROR! Board::RemoveBlackPawn(const unsigned short number) Requesting white " << number << " pawn not exist!";
    };

    eraseBlack(number);
}

void Board::RemoveWhitePawn(const unsigned short number)
{
    if (number>numberOfWhite()-1)
    {
        Traces() << "\n" << "ERROR! Board::RemoveWhitePawn(const unsigned short number) Requesting white " << number << " pawn not exist!";
    };

    eraseWhite(number);
}

PawnPos Board::GetWhitePawnPos(const unsigned short number)
{
    if (number>numberOfWhite()-1)
    {
        Traces() << "\n" << "ERROR! GetWhitePawnPos(const unsigned short number) Requesting " << number << " white pawn not exist!";
    } else        
    {
        Pawn temp = white[number];
        return PawnPos(temp.x, temp.y);
    };
    return PawnPos(0,0);
}

PawnPos Board::GetBlackPawnPos(const unsigned short number)
{
    if (number>numberOfBlack()-1)
    {        
        Traces() << "\n" << "ERROR! GetBlackPawnPos(const unsigned short number) Requesting black " << number << " pawn not exist!";
    } else
    {
        Pawn temp = black[number];
        return PawnPos(temp.x, temp.y);        
    };
    return PawnPos(0,0);
}

bool Board::GetWhitePawnPons(const unsigned short number)
{
    if (number>numberOfWhite()-1)
    {
        Traces() << "\n" << "ERROR! GetWhitePawnPons(const unsigned short number) Requesting white " << number << " pawn not exist!";
    } else
    {
        Pawn temp = white[number];
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
    if (number>numberOfBlack()-1)
    {        
        Traces() << "\n" << "ERROR! GetBlackPawnPons(const unsigned short number) Requesting black pawn not exist!";
    } else
    {
        Pawn temp = black[number];
        return temp.pons;
    };
    return 0;
}

bool Board::SetWhitePawnPons(const unsigned short number, const bool flag)
{
    if (number>numberOfWhite()-1)
    {
        Traces() << "\n" << "ERROR! Board::SetWhitePawnPons(const unsigned short number, const bool flag) Requesting white pawn not exist!";
    } else
    {
        Pawn &ref = white[number];
        ref.pons = flag;
    };
}

bool Board::SetBlackPawnPons(const unsigned short number, const bool flag)
{
    if (number>numberOfBlack()-1)
    {
        Traces() << "\n" << "ERROR! Board::SetWhitePawnPons(const unsigned short number, const bool flag) Requesting white pawn not exist!";
    } else
    {
        Pawn &ref = black[number];
        ref.pons = flag;
    };
}

bool Board::IsPawnOnPos(const unsigned short x, const unsigned short y)
{    
    for (unsigned short i=0;i <numberOfWhite();i++)
    {
        if ((white[i].x == x)&&(white[i].y == y))
        {
            return 1;
        };
    };    

    for (unsigned short i=0;i <numberOfBlack();i++)
    {
        if ((black[i].x == x)&&(black[i].y == y))
        {
            return 1;
        };
    };

    return 0;
}

bool Board::IsWhitePawnOnPos(const unsigned short x, const unsigned short y)
{
    for (unsigned short i=0;i <numberOfWhite();i++)
    {
        if ((white[i].x == x)&&(white[i].y == y))
        {
            return 1;
        };
    };

    return 0;
}

bool Board::IsBlackPawnOnPos(const unsigned short x, const unsigned short y)
{
    for (unsigned short i=0;i <numberOfBlack();i++)
    {
        if ((black[i].x == x)&&(black[i].y == y))
        {
            return 1;
        };
    };

    return 0;
}

unsigned short Board::GetNumberOfWhite()
{
   return numberOfWhite();
}

unsigned short Board::GetNumberOfBlack()
{
    return numberOfBlack();
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

    for (unsigned short i=0;i <numberOfWhite();i++)
    {
        if ((white[i].x == x)&&(white[i].y == y))
        {
            eraseWhite(counter);
            flag = 1;
        };
        counter ++;
    };

    counter = 0;
    for (unsigned short i=0;i <numberOfBlack();i++)
    {
        if ((black[i].x == x)&&(black[i].y == y))
        {
            eraseBlack(counter);
            flag = 1;
        };
        counter ++;
    };

    if (!flag) Traces() << "\n" << "ERROR! Board::RemovePonsFrom(const unsigned short x, const unsigned short y) Requesting pawn that not exist!";
}

void Board::SetPreviousMurder(const unsigned short number)
{
    if ((number>=0)&&(number<=12))
    {
        previousMurder = number;
    } else
    {
        Traces() << "\n" << "ERROR! IADecisionTree::SetPreviousMurder(const unsigned short number) Out of range 0-12! Trying to set " << number;
    };
}

unsigned short Board::GetPreviousMurder()
{
    return previousMurder;
}

unsigned short Board::GetResult()
{
    unsigned short result;

    result = numberOfWhite();
    result+= -(numberOfBlack() - 12);

    return result;
}

double Board::GetPercentageResult()
{
    Traces() << "\n" << "LOG: Board::GetPercentageResult() = " << (double)numberOfBlack() / (double)numberOfWhite();
    return (double)numberOfBlack() / (double)numberOfWhite();
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

    clearWhite();
    clearBlack();

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
             white[numberOfWhite()] = Pawn(realPositionX,y,0,0);
             realPositionX += 1;
           } else
           if (data[position] == 'W')
           {
             white[numberOfWhite()] = Pawn(realPositionX,y,0,1);

             realPositionX += 1;
           } else
           if (data[position] == 'b')
           {
             black[numberOfBlack()] = Pawn(realPositionX,y,0,0);
             realPositionX += 1;
           } else
           if (data[position] == 'B')
           {
             black[numberOfBlack()] = Pawn(realPositionX,y,0,1);

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

    clearWhite();
    clearBlack();

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
             white[numberOfWhite()] = Pawn(realPositionX,y,0,0);
             realPositionX += 1;
           } else
           if (data[position] == 'W')
           {
             white[numberOfWhite()] = Pawn(realPositionX,y,0,1);

             realPositionX += 1;
           } else
           if (data[position] == 'b')
           {
             black[numberOfBlack()] = Pawn(realPositionX,y,0,0);

             realPositionX += 1;
           } else
           if (data[position] == 'B')
           {
             black[numberOfBlack()] = Pawn(realPositionX,y,0,1);

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

unsigned short Board::numberOfWhite()
{
    unsigned short size = 0;

    for (unsigned short i=0;i<12;i++)
    {
        if (!white[i].dead) size++;
    };
    return size;
}

unsigned short Board::numberOfBlack()
{
    unsigned short size = 0;

    for (unsigned short i=0;i<12;i++)
    {
        if (!black[i].dead) size++;
    };
    return size;
}

void Board::eraseWhite(unsigned short num)
{
    unsigned short numW = numberOfWhite();
    if (numW == 1)
    {
        white[0].dead = true;
    } else
    if (num == numW)
    {
        white[num].dead = true;
    } else
    {
        for (unsigned short i=num;i<numW;i++)
        {
            white[i] = white[i+1];
        };
        white[numW-1].dead = true;
    };
}

void Board::eraseBlack(unsigned short num)
{
    unsigned short numB = numberOfBlack();
    if (numB == 1)
    {
        black[0].dead = true;
    } else
    if (num == numB)
    {
        black[num].dead = true;
    } else
    {
        for (unsigned short i=num;i<numB;i++)
        {
            black[i] = black[i+1];
        };
        black[numB-1].dead = true;
    };
}

void Board::clearWhite()
{
    for (unsigned short i=0;i<12;i++)
    {
        white[i].dead = true;
    };
}

void Board::clearBlack()
{
    for (unsigned short i=0;i<12;i++)
    {
        black[i].dead = true;
    };
}

void Board::CopyTo(ThreadIASimpleBoard & data)
{
    for (unsigned short i=0;i<12;i++)
    {
        data.black[i] = black[i];
        data.white[i] = white[i];
    };
}

void Board::CopyFrom(const ThreadIASimpleBoard & data)
{
    for (unsigned short i=0;i<12;i++)
    {
        black[i] = data.black[i];
        white[i] = data.white[i];
    };
}

void Board::SetOrigin(Board & data)
{
    data.CopyTo(origin);
}

void Board::StartBlack()
{
    blackWhite = 0;
}

void Board::StartWhite()
{
    blackWhite = 1;
}

bool Board::Black()
{
    return !blackWhite;
}

bool Board::White()
{
    return blackWhite;
}
