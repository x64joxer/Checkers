#ifndef PROGRAMVARIABLES_H
#define PROGRAMVARIABLES_H

#include <QString>
#include <mutex>
#include <thread>
#include <condition_variable>

class ProgramVariables
{
    public:
        ProgramVariables();
        static unsigned short GetNumberOfThreads();
        static unsigned short GetMaxNumberOfThreads();
        static void SetNumberOfThreads(const unsigned short num);
        static bool IsWorker();
        static void SetWorker(const bool flag);
        static unsigned long GetSecondsSinceEpoch();
        static unsigned long GetMaxSecondsToEnd();
        static unsigned long GetMaxTimeWaitToWorkers();
        static unsigned long GetMaxTimeWaitToServer();
        static unsigned int GetRecconectingTime();
        static unsigned short GetMaxNumberOfReattempt();
        static QString GetServerIP();
        static int GetServerPort();
        static std::condition_variable * GetGlobalConditionVariable();
        static std::string CreateMessageId();        

        static const unsigned int K4 =  4 * 1024;

    private:
        static unsigned short InitMaxThreads();

        static unsigned short maxNumbeOfThreads;
        static unsigned short numbeOfThreads;
        static bool isWorker;
        static unsigned long messageId;
        static std::mutex mutex_guard;
        static std::condition_variable condition_var;
};

#endif // PROGRAMVARIABLES_H
