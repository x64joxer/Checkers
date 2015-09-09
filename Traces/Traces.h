#ifndef TRACES_H
#define TRACES_H

#include <ostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <qdebug.h>
#include <string>
#include <sstream>
#include <set>
#include <QString>

class Traces
{
    public:
        Traces();

        //Traces& operator <<(std::string);
        Traces& operator <<(QString );
        Traces& operator <<(long);

        static unsigned long int GetCurrentTime();
        static std::string GetCurrentDate();

        static void TurnOnTraces();
        static void TurnOffTraces();
        static bool GetTraceFlag();
        static void RemoveThreadID();

    private:
        static std::string patchAndNameFile;
        inline void StringToFile(std::string log);
        static bool traceOn;
        static std::mutex mutex;
        static std::map<unsigned long int,std::string> theardsId;
        static std::set<std::string> idText;

        static unsigned long int GetThreadId();
        bool IsOnTheList();
        std::string GetThreadText();
        std::string CreateNewThreadText();        
        std::string FindFirstFreeId();
        static std::string GenerateText(int);

        static bool timeFlag;
        static unsigned long int start,stop;
        static std::string traceFolder;
};

#endif // TRACES_H
