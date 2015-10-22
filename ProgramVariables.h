#ifndef PROGRAMVARIABLES_H
#define PROGRAMVARIABLES_H

#include <thread>

class ProgramVariables
{
    public:
        ProgramVariables();
        static unsigned short GetNumberOfThreads();
        static unsigned short GetMaxNumberOfThreads();
        static void SetNumberOfThreads(const unsigned short num);
        static bool IsWorker();
        static void SetWorker(const bool flag);

    private:
        static unsigned short InitMaxThreads();

        static unsigned short maxNumbeOfThreads;
        static unsigned short numbeOfThreads;
        static bool isWorker;

};

#endif // PROGRAMVARIABLES_H
