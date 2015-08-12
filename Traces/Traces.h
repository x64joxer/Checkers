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

class Traces
{
    public:
        Traces();
        Traces& operator <<(std::string);
        Traces& operator <<(long);
        static void SetPatch(const std::string &patchAndName);

    private:
        static std::string patchAndNameFile;
        void StringToFile(std::string & log);
        static std::ofstream logFile;
};

#endif // TRACES_H
