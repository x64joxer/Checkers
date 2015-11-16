#ifndef WORKERTCP_H
#define WORKERTCP_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include "Traces/Traces.h"
#include "TCP/MessageCoder.h"
#include "ThreadIA/ThreadIAMove.h"

class WorkerTCP : public QObject
{
    Q_OBJECT

    public:
        explicit WorkerTCP(QObject *parent = 0);
        ~WorkerTCP();

        void ConnectToServer(const QString ho, int po);

        enum MessageState { NONE_OK, STATE_OK, BEST_RESULT_OK };
    signals:

    public slots:
        void ReadDataFromServer();
        void Reconnect();
        void ConnectionError(QAbstractSocket::SocketError socketError);
        void Connected();
        void HandleStateChange(QAbstractSocket::SocketState socketState);
        void MessageInterpreting(const std::map<std::string, std::string> data);

        void TakeStartWork(const std::map<std::string, std::string> data);

    private slots:
        void CheckStatus();
        void NoResponseFromServer();

    private:        
        void Init();
        void SendStateMessage();
        void SendBestResultMessage();
        bool IsEndMessage(const char* data, const unsigned int end, const char *text);

        QTcpSocket *tcpSocket;
        enum ConState { DISCONNECTED, CONNECTED} connection_state;
        MessageState messageState;
        unsigned short numOfReattempt;
        QTimer *time;
        QString host;
        Peers::STATE state;
        int port;

        std::thread iaJob;
        std::atomic_bool endIaJobFlag;
        std::atomic<int> currentPercentOfSteps;
        ThreadIAMove<900000> jobExpander;

        QTimer *waitForIATimer;
        QTimer *waitForOKMessageTimer;
        std::string waitForOKMessageID;
        std::string jobId;
        Board *board;
        unsigned int timeSteps;
        char *globalData;
        unsigned int globalLength;

};

#endif // WORKERTCP_H
