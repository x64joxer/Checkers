#ifndef PROGRAMVARIABLES_H
#define PROGRAMVARIABLES_H

#include <thread>

class ProgramVariables
{
    public:
        ProgramVariables();
        static unsigned short GetNumberOfThreads();
        static unsigned short GetMaxNumberOfThreads();

    private:
        static unsigned short InitMaxThreads();

        static unsigned short maxNumbeOfThreads;
        static unsigned short numbeOfThreads;

};

#endif // PROGRAMVARIABLES_H
