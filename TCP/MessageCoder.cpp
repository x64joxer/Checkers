#include "TCP/MessageCoder.h"

MessageCoder::MessageCoder()
{

}

void MessageCoder::KeyValuePairToChar(const std::string key, const std::string value, char *dest)
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

void MessageCoder::KeyValuePairToChar(const std::string key, const int value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string key, const short value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string key, const long value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string key, const unsigned short value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string key, const unsigned long value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::KeyValuePairToChar(const std::string key, const bool value, char *dest)
{
    KeyValuePairToChar(key, std::to_string(value), dest);
}

void MessageCoder::ClearChar(char *dest, const unsigned int num)
{
    for (unsigned int i=0;i<num;i++) dest[i] = 0;
}
