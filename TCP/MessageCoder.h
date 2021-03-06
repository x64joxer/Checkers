#ifndef MESSAGECODER_H
#define MESSAGECODER_H

#include "ProgramVariables.h"
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
        static void KeyValuePairToChar(const std::string & key, const unsigned long long value, char *dest);
        static void KeyValuePairToChar(const std::string & key, const bool value, char *dest);

        static void BoardToChar(const Board & board, char *dest, const unsigned short numberOfBoard);
        static void CreateStartMessage(const unsigned short respTime, const unsigned short numberOfBoard,  const std::string & id, const std::string & jobId, char *dest);
        static void CreateBestResultMessage(const std::string & id, const std::string & jobId, unsigned long long numOfAnalysed, char *dest);
        static void CreateStateMessage(const Peers::STATE stat, const std::string & id, char *dest);
        static void CreateOkMessage(const std::string & id, char *dest);

        static void ClearChar(char *dest, const unsigned int num);

        static void MessageToMap(const char *source, std::map<std::string, std::string> & dest);
        static void MapToBoard(const std::map<std::string, std::string> & dest, Board *board);        

        //Keys
        static std::string ACTION;
        static std::string OK;
        static std::string MESSAGE_ID;
        static std::string MESSAGE_END;

        static std::string START_WORK;
        static std::string SET_STATE;        
        static std::string BEST_RESULT;

        static std::string MAX_TIME;
        static std::string NUM_OF_ANALYSED;
        static std::string NUM_OF_BOARD;
        static std::string STATE;
        static std::string JOB_ID;
        static std::string NUM_OF_THREAD;

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

     private:
        static std::string GetNextKey(const std::string & debug_key);
        static unsigned int nextKey;
        static bool debugMode;

};

#endif // MESSAGECODER_H
