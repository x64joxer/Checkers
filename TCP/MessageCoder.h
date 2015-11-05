#ifndef MESSAGECODER_H
#define MESSAGECODER_H

#include "Traces/Traces.h"

class MessageCoder
{
    public:
        MessageCoder();
        static void KeyValuePairToChar(const std::string key, const std::string value, char *dest);

        static void KeyValuePairToChar(const std::string key, const int value, char *dest);
        static void KeyValuePairToChar(const std::string key, const short value, char *dest);
        static void KeyValuePairToChar(const std::string key, const long value, char *dest);
        static void KeyValuePairToChar(const std::string key, const unsigned short value, char *dest);
        static void KeyValuePairToChar(const std::string key, const unsigned long value, char *dest);
        static void KeyValuePairToChar(const std::string key, const bool value, char *dest);

        static void ClearChar(char *dest, const unsigned int num);
};

#endif // MESSAGECODER_H
