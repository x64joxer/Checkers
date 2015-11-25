#include "TCP/MessageCoder.h"

MessageCoder::MessageCoder()
{

}

void MessageCoder::KeyValuePairToChar(const std::string & key, const std::string & value, char *dest)
{
        int len = strlen(dest);

        dest[len] = '<';
        dest[len+1] = 0;

        std::copy(key.begin(), key.end(), dest + strlen(dest));
        dest[strlen(dest)] = 0;

        len = strlen(dest);
        dest[len] = '>';       
        dest[len+1] = '<';
        dest[len+2] = 0;
        len = len +2;
        std::copy(value.begin(), value.end(), dest + strlen(dest));
        len = strlen(dest);
        dest[len] = '>';
        dest[len+1] = 0;
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const int value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const short value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const long value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const unsigned short value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const unsigned long long value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string & key, const bool value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::ClearChar(char *dest, const unsigned int num)
{
    for (unsigned int i=0;i<num;i++) dest[i] = 0;
}

void MessageCoder::MessageToMap(const char *source, std::map<std::string, std::string> & dest)
{
    unsigned int i = 0;
    unsigned int begin;
    unsigned int end;
    unsigned int begin_val;
    unsigned int end_val;
    std::string keyString;
    bool key = false;

    while (source[i] != 0)
    {
        if (!key)
        {
            if (source[i] == '<') begin = i;
            if (source[i] == '>')
            {
                end = i;
                key = true;
            };
        } else
        {
            if (source[i] == '<') begin_val = i;
            if (source[i] == '>')
            {
                end_val = i;
                key = false;
                keyString = std::string(source + begin + 1, source + end);
                dest[keyString] = std::string(source + begin_val + 1, source + end_val);
            };
        }

        if (keyString == MESSAGE_END) break;

        i++;
    };
}

void MessageCoder::BoardToChar(const Board &board, char *dest, const unsigned short numberOfBoard)
{
    TRACE01 Traces() << "\n" << "LOG: MessageCoder::BoardToChar(const Board &board, char *dest, const unsigned short numberOfBoard)";    

    KeyValuePairToChar(PREVIOUS_MURDER, board.GetPreviousMurder(), dest);
    KeyValuePairToChar(WHITE_PATCH_END, board.GetWhitePatchEnd(), dest);
    KeyValuePairToChar(BLACK_WHITE, board.Black(), dest);

    //Origin

    Board temp = board.GetOrigin();
    std::string prefix = std::to_string(numberOfBoard) + "_";
    PawnPos pawnPos;
    unsigned short num;

    num = temp.GetNumberOfBlack();
    KeyValuePairToChar(prefix + ORIGIN_NUMBER_BLACK, num, dest);

    if (num > 0)
    {
        for (unsigned short i = 0; i<num; i++)
        {
            pawnPos = temp.GetBlackPawnPos(i);
            KeyValuePairToChar(prefix + ORIGIN_BLACK_X + std::to_string(i), pawnPos.X(), dest);
            KeyValuePairToChar(prefix + ORIGIN_BLACK_Y + std::to_string(i), pawnPos.Y(), dest);
            KeyValuePairToChar(prefix + ORIGIN_BLACK_PONS + std::to_string(i), temp.GetBlackPawnPons(i), dest);
        }
    }

    num = temp.GetNumberOfWhite();
    KeyValuePairToChar(prefix + ORIGIN_NUMBER_WHITE, num, dest);

    if (num > 0)
    {
        for (unsigned short i = 0; i<num; i++)
        {
            pawnPos = temp.GetWhitePawnPos(i);
            KeyValuePairToChar(prefix + ORIGIN_WHITE_X + std::to_string(i), pawnPos.X(), dest);
            KeyValuePairToChar(prefix + ORIGIN_WHITE_Y + std::to_string(i), pawnPos.Y(), dest);
            KeyValuePairToChar(prefix + ORIGIN_WHITE_PONS + std::to_string(i), temp.GetWhitePawnPons(i), dest);
        }
    }


    //Board

    num = board.GetNumberOfBlack();
    KeyValuePairToChar(prefix + NUMBER_BLACK, num, dest);

    TRACE01 board.printDebug();

    if (num > 0)
    {
        for (unsigned short i = 0; i<num; i++)
        {            
            pawnPos = board.GetBlackPawnPos(i);
            KeyValuePairToChar(prefix + BLACK_X + std::to_string(i), pawnPos.X(), dest);            
            KeyValuePairToChar(prefix + BLACK_Y + std::to_string(i), pawnPos.Y(), dest);           
            KeyValuePairToChar(prefix + BLACK_PONS + std::to_string(i), board.GetBlackPawnPons(i), dest);
        }
    }

    num = board.GetNumberOfWhite();
    KeyValuePairToChar(prefix + NUMBER_WHITE, num, dest);

    if (num > 0)
    {
        for (unsigned short i = 0; i<num; i++)
        {
            pawnPos = board.GetWhitePawnPos(i);
            KeyValuePairToChar(prefix + WHITE_X + std::to_string(i), pawnPos.X(), dest);
            KeyValuePairToChar(prefix + WHITE_Y + std::to_string(i), pawnPos.Y(), dest);
            KeyValuePairToChar(prefix + WHITE_PONS + std::to_string(i), board.GetWhitePawnPons(i), dest);
        }
    }

    KeyValuePairToChar(MESSAGE_END, 0, dest);
}

void MessageCoder::MapToBoard(const std::map<std::string, std::string> & dest, Board *board)
{
    try
    {
        board->Clear();

        board->SetPreviousMurder(atoi(dest.at(PREVIOUS_MURDER).c_str()));
        board->SetWhitePatchEnd(atoi(dest.at(WHITE_PATCH_END).c_str()));

        if (atoi(dest.at(BLACK_WHITE).c_str()) == 0)
        {
            board->StartBlack();
        } else
        {
            board->StartWhite();
        }

        Board origin;
        std::string prefix = "1_";

        std::string temp;
        std::string tempX;
        std::string tempY;
        std::string tempPons;

        temp = dest.at(prefix + ORIGIN_NUMBER_BLACK);
        unsigned short numBlack = atoi(temp.c_str());
        temp = dest.at(prefix + ORIGIN_NUMBER_WHITE);
        unsigned short numWhite = atoi(temp.c_str());

        if (numBlack > 0)
        {
            for (unsigned short i = 0; i<numBlack; i++)
            {
                tempX = dest.at(prefix + ORIGIN_BLACK_X + std::to_string(i));
                tempY = dest.at(prefix + ORIGIN_BLACK_Y + std::to_string(i));
                tempPons = dest.at(prefix + ORIGIN_BLACK_PONS + std::to_string(i));

                origin.AddBlackPawn(atoi(tempX.c_str()),
                                    atoi(tempY.c_str()),
                                    0,
                                    atoi(tempPons.c_str()));
            }
        }


        if (numWhite > 0)
        {
            for (unsigned short i = 0; i<numWhite; i++)
            {
                tempX = dest.at(prefix + ORIGIN_WHITE_X + std::to_string(i));
                tempY = dest.at(prefix + ORIGIN_WHITE_Y + std::to_string(i));
                tempPons = dest.at(prefix + ORIGIN_WHITE_PONS + std::to_string(i));

                origin.AddWhitePawn(atoi(tempX.c_str()),
                                    atoi(tempY.c_str()),
                                    0,
                                    atoi(tempPons.c_str()));
            }
        }

        board->SetOrigin(origin);

        temp = dest.at(prefix + NUMBER_BLACK);
        numBlack = atoi(temp.c_str());
        temp = dest.at(prefix + NUMBER_WHITE);
        numWhite = atoi(temp.c_str());

        if (numBlack > 0)
        {
            for (unsigned short i = 0; i<numBlack; i++)
            {
                tempX = dest.at(prefix + BLACK_X + std::to_string(i));
                tempY = dest.at(prefix + BLACK_Y + std::to_string(i));
                tempPons = dest.at(prefix + BLACK_PONS + std::to_string(i));

                board->AddBlackPawn(atoi(tempX.c_str()),
                                    atoi(tempY.c_str()),
                                    0,
                                    atoi(tempPons.c_str()));
            }
        }

        if (numWhite > 0)
        {
            for (unsigned short i = 0; i<numWhite; i++)
            {
                tempX = dest.at(prefix + WHITE_X + std::to_string(i));
                tempY = dest.at(prefix + WHITE_Y + std::to_string(i));
                tempPons = dest.at(prefix + WHITE_PONS + std::to_string(i));

                board->AddWhitePawn(atoi(tempX.c_str()),
                                    atoi(tempY.c_str()),
                                    0,
                                    atoi(tempPons.c_str()));
            }
        }
    }
    catch (std::out_of_range)
    {
        throw;
    }
}

void MessageCoder::CreateStartMessage(const unsigned short respTime, const unsigned short numberOfBoard, std::string id, std::string jobId, char *dest)
{    
    KeyValuePairToChar(ACTION, START_WORK, dest);
    KeyValuePairToChar(MAX_TIME, respTime, dest);
    KeyValuePairToChar(MESSAGE_ID, id, dest);
    KeyValuePairToChar(JOB_ID, jobId, dest);
    KeyValuePairToChar(NUM_OF_BOARD, numberOfBoard, dest);
}

void MessageCoder::CreateBestResultMessage(const std::string id, const std::string jobId, unsigned long long numOfAnalysed, char *dest)
{
    KeyValuePairToChar(ACTION, BEST_RESULT, dest);
    KeyValuePairToChar(NUM_OF_ANALYSED, numOfAnalysed, dest);
    KeyValuePairToChar(MESSAGE_ID, id, dest);
    KeyValuePairToChar(JOB_ID, jobId, dest);    
}

void MessageCoder::CreateStateMessage(Peers::STATE stat, const std::string id, char *dest)
{
    KeyValuePairToChar(ACTION, SET_STATE, dest);
    KeyValuePairToChar(MESSAGE_ID, id, dest);
    KeyValuePairToChar(STATE, stat, dest);
    KeyValuePairToChar(MESSAGE_END, 0, dest);
}

void MessageCoder::CreateOkMessage(const std::string id, char *dest)
{
    KeyValuePairToChar(ACTION, OK, dest);
    KeyValuePairToChar(MESSAGE_ID, id, dest);
    KeyValuePairToChar(MESSAGE_END, 0, dest);
}

std::string MessageCoder::ACTION = "ACTION";
std::string MessageCoder::OK = "OK";
std::string MessageCoder::MESSAGE_ID = "MESSAGE_ID";
std::string MessageCoder::MESSAGE_END = "MESSAGE_END";

std::string MessageCoder::START_WORK = "START_WORK";
std::string MessageCoder::SET_STATE = "SET_STATE";
std::string MessageCoder::BEST_RESULT = "BEST_RESULT";

std::string MessageCoder::MAX_TIME = "MAX_TIME";
std::string MessageCoder::NUM_OF_ANALYSED = "NUM_OF_ANALYSED";
std::string MessageCoder::NUM_OF_BOARD = "NUM_OF_BOARD";
std::string MessageCoder::STATE =  "STATE";
std::string MessageCoder::JOB_ID = "JOB_ID";

std::string MessageCoder::PREVIOUS_MURDER = "PREVIOUS_MURDER";
std::string MessageCoder::WHITE_PATCH_END = "WHITE_PATCH_END";
std::string MessageCoder::BLACK_WHITE = "BLACK_WHITE";

std::string MessageCoder::ORIGIN_NUMBER_BLACK = "ORIGIN_NUMBER_BLACK";
std::string MessageCoder::ORIGIN_NUMBER_WHITE = "ORIGIN_NUMBER_WHITE";
std::string MessageCoder::ORIGIN_WHITE_X = "ORIGIN_WHITE_X_" ;
std::string MessageCoder::ORIGIN_WHITE_Y = "ORIGIN_WHITE_Y_" ;
std::string MessageCoder::ORIGIN_BLACK_X = "ORIGIN_BLACK_X_" ;
std::string MessageCoder::ORIGIN_BLACK_Y = "ORIGIN_BLACK_Y_" ;
std::string MessageCoder::ORIGIN_WHITE_PONS = "ORIGIN_WHITE_PONS_" ;
std::string MessageCoder::ORIGIN_BLACK_PONS = "ORIGIN_BLACK_PONS_" ;

std::string MessageCoder::NUMBER_BLACK = "NUMBER_BLACK";
std::string MessageCoder::NUMBER_WHITE = "NUMBER_WHITE";
std::string MessageCoder::WHITE_X = "WHITE_X_" ;
std::string MessageCoder::WHITE_Y = "WHITE_Y_" ;
std::string MessageCoder::BLACK_X = "BLACK_X_" ;
std::string MessageCoder::BLACK_Y = "BLACK_Y_" ;
std::string MessageCoder::WHITE_PONS = "WHITE_PONS_" ;
std::string MessageCoder::BLACK_PONS = "BLACK_PONS_" ;

