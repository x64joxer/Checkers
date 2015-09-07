#include "Traces.h"

Traces::Traces()
{

}

/*Traces& Traces::operator <<(std::string data)
{
    qDebug() << "Operator";
    StringToFile(data);
}*/

unsigned long int Traces::GetThreadId()
{
    std::stringstream ss;
    ss << std::this_thread::get_id();
    uint64_t id = std::stoull(ss.str());
    return id;
}

bool Traces::IsOnTheList()
{

    if (theardsId.empty()) return false;

    if (theardsId.find(GetThreadId()) != theardsId.map::end())
    {
        return true;
    };
    return false;
}

std::string Traces::CreateNewThreadText()
{
    std::string result;

    if (theardsId.empty())
    {
      result = GenerateText(1);
      theardsId[GetThreadId()] = result;
      idText.insert(result);
    } else
    {
        result = FindFirstFreeId();
        theardsId[GetThreadId()] = result;
        idText.insert(result);
    };

    return result;
}

std::string Traces::GenerateText(int i)
{
    return "thread_" + std::to_string(i);
}

std::string Traces::FindFirstFreeId()
{
    int id = 1;
    auto search = idText.find(GenerateText(id));

    while(search != idText.end())
    {        
        id++;
        search = idText.find(GenerateText(id));
    };
    return GenerateText(id);
}

std::string Traces::GetThreadText()
{
    if (IsOnTheList())
    {
       return theardsId[GetThreadId()];
    };

    return CreateNewThreadText();
}

Traces& Traces::operator <<(QString data)
{    
    if (traceOn)
    {
        std::lock_guard<std::mutex> guard(mutex);
        StringToFile(data.toStdString());
    };
}

Traces& Traces::operator <<(long data)
{    
    if (traceOn)
    {  
        std::lock_guard<std::mutex> guard(mutex);
        std::string number;
        std::stringstream strstream;
        strstream << data;
        strstream >> number;
        StringToFile(number);        
    };
}

unsigned long int Traces::GetCurrentTime()
{
    if (!timeFlag)
    {
        start = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        timeFlag = true;
    } else
    {
        stop = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        timeFlag = false;       
        qDebug() << "Diff=" << stop - start;
        return stop - start;
    };    

    return 0;
}

std::string Traces::GetCurrentDate()
{
    std::string result;
    unsigned long milliseconds_since_epoch = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    unsigned long counter = 1000000000;

    while (counter != 1)
    {
        result += std::to_string(milliseconds_since_epoch / counter) + ",";
        milliseconds_since_epoch = milliseconds_since_epoch % counter;
        counter = counter / 1000;
    };
    result += std::to_string(milliseconds_since_epoch);
    return result;
}

void Traces::StringToFile(std::string log)
{
    static std::ofstream logFile;
    logFile.open (traceFolder + GetThreadText().c_str(),std::ofstream::in | std::ofstream::app);

    if (log == "\n") log += GetThreadText() + "[" + GetCurrentDate() + "]";

    logFile << log;
    logFile.close();
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
bool Traces::traceOn = false;
std::mutex Traces::mutex;
std::map<unsigned long int,std::string> Traces::theardsId;
std::set<std::string> Traces::idText;
bool Traces::timeFlag = false;
unsigned long int Traces::start =0;
unsigned long int Traces::stop =0;
std::string Traces::traceFolder = "traces/";
