#ifndef TRACES_H
#define TRACES_H

#include <ostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <qdebug.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <QString>

class Traces
{
    public:
        Traces();

        //Traces& operator <<(std::string);
        Traces& operator <<(QString);
        Traces& operator <<(long);

        std::string GetCurrentDate();

        static void TurnOnTraces();
        static void TurnOffTraces();      

    private:
        static std::string patchAndNameFile;
        inline void StringToFile(std::string log);
        static bool traceOn;
        static std::mutex mutex;
        static std::map<unsigned long int,std::string> theardsId;
        static std::set<std::string> idText;

        unsigned long int GetThreadId();
        bool IsOnTheList();
        std::string GetThreadText();
        std::string CreateNewThreadText();        
        std::string FindFirstFreeId();
        std::string GenerateText(int);        
};

#endif // TRACES_H
