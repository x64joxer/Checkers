#include "Traces.h"

Traces::Traces()
{

}

Traces& Traces::operator <<(std::string data)
{
    StringToFile(data);
}

Traces& Traces::operator <<(long data)
{
    std::string number;
    std::stringstream strstream;
    strstream << data;
    strstream >> number;
    StringToFile(number);
}

void Traces::SetPatch(const std::string &patchAndName)
{
    if (patchAndNameFile == "")
    {
        patchAndNameFile = patchAndName;
        logFile.open (patchAndNameFile.c_str());
    };
}

void Traces::StringToFile(std::string & log)
{
    logFile << log;
}


std::string Traces::patchAndNameFile ="";
std::ofstream Traces::logFile;
