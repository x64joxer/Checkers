#include "Traces.h"

Traces::Traces()
{

}

/*Traces& Traces::operator <<(std::string data)
{
    qDebug() << "Operator";
    StringToFile(data);
}*/

Traces& Traces::operator <<(QString data)
{
    if (traceOn)  StringToFile(data.toStdString());
}

Traces& Traces::operator <<(long data)
{
    if (traceOn)
    {  
        std::string number;
        std::stringstream strstream;
        strstream << data;
        strstream >> number;
        StringToFile(number);
    };
}

void Traces::SetPatch(const std::string &patchAndName)
{
    if (patchAndNameFile == "")
    {
        patchAndNameFile = patchAndName;
        logFile.open (patchAndNameFile.c_str());
    };
}

void Traces::StringToFile(std::string log)
{    
    logFile << log;
}

void Traces::TurnOnTraces()
{
    traceOn = true;
}

void Traces::TurnOffTraces()
{
    traceOn = false;
}

std::string Traces::patchAndNameFile ="";
std::ofstream Traces::logFile;
bool Traces::traceOn = false;
