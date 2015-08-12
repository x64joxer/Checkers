#ifndef TRACES_H
#define TRACES_H

#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <qdebug.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <QString>

class Traces
{
    public:
        Traces();

        //Traces& operator <<(std::string);
        Traces& operator <<(QString);
        Traces& operator <<(long);

        static void TurnOnTraces();
        static void TurnOffTraces();
        static void SetPatch(const std::string &patchAndName);

    private:
        static std::string patchAndNameFile;
        void StringToFile(std::string log);
        static std::ofstream logFile;
        static bool traceOn;
};

#endif // TRACES_H
