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
        static unsigned long long GetSecondsSinceEpoch();
        static unsigned long long GetMaxSecondsToEnd();
        static unsigned long long GetMaxTimeForIa();
        static unsigned long long GetMaxTimeWaitToWorkers();
        static unsigned long long GetMaxTimeWaitToServer();
        static unsigned int GetRecconectingTime();
        static unsigned short GetMaxNumberOfReattempt();
        static QString GetServerIP();
        static int GetServerPort();
        static std::condition_variable * GetGlobalConditionVariable();
        static std::condition_variable * GetGlobalConditionVariableNetwork();
        static void NotifyOne();
        static std::string CreateMessageId();        
        static void SetNumOfAnalyded(const unsigned long long val) { numOfAnalysded = val; }
        static unsigned long long GetNumOfAnalyded() { return numOfAnalysded; }

        static const unsigned int K4 =  4 * 1024;

    private:
        static unsigned short InitMaxThreads();

        static unsigned short maxNumbeOfThreads;
        static unsigned short numbeOfThreads;
        static bool isWorker;
        static unsigned long long messageId;
        static std::mutex mutex_guard;
        static std::condition_variable condition_var;
        static std::condition_variable condition_var_network;
        static unsigned long long numOfAnalysded;
};

#endif // PROGRAMVARIABLES_H
