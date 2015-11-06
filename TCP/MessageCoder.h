#ifndef MESSAGECODER_H
#define MESSAGECODER_H

#include "Traces/Traces.h"
#include "Board.h"
#include "PawnPos.h"
#include "Peers.h"

class MessageCoder
{
    public:
        MessageCoder();
        static void KeyValuePairToChar(const std::string & key, const std::string & value, char *dest);

        static void KeyValuePairToChar(const std::string & key, const int value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const short value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const long value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const unsigned short value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const unsigned long value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const bool value, char *dest);

        static void BoardToChar(const Board &board, char *dest, const unsigned short numberOfBoard);
        static void CreateStartMessage(const unsigned short respTime, const unsigned short numberOfBoard, char *dest);
        static void CreateStateMessage(Peers::STATE stat, char *dest);

        static void ClearChar(char *dest, const unsigned int num);

        //Keys
        static std::string START_WORK;
        static std::string SET_STATE;

        static std::string MAX_TIME;
        static std::string NUM_OF_BOARD;
        static std::string STATE;

        static std::string PREVIOUS_MURDER;
        static std::string WHITE_PATCH_END;
        static std::string  BLACK_WHITE;

        static std::string  ORIGIN_NUMBER_BLACK;
        static std::string  ORIGIN_NUMBER_WHITE;
        static std::string  ORIGIN_WHITE_X;
        static std::string ORIGIN_BLACK_X;
        static std::string  ORIGIN_WHITE_Y;
        static std::string ORIGIN_BLACK_Y;
        static std::string ORIGIN_WHITE_PONS;
        static std::string ORIGIN_BLACK_PONS;

        static std::string  NUMBER_BLACK;
        static std::string  NUMBER_WHITE;
        static std::string  WHITE_X;
        static std::string BLACK_X;
        static std::string  WHITE_Y;
        static std::string BLACK_Y;
        static std::string WHITE_PONS;
        static std::string BLACK_PONS;

};

#endif // MESSAGECODER_H
