#ifndef WORKERTCP_H
#define WORKERTCP_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include "Traces/Traces.h"
#include "TCP/MessageCoder.h"

class WorkerTCP : public QObject
{
    Q_OBJECT

    public:
        explicit WorkerTCP(QObject *parent = 0);
        ~WorkerTCP();

        void ConnectToServer(const QString ho, int po);

    signals:

    public slots:
        void ReadDataFromServer();
        void Reconnect();
        void ConnectionError(QAbstractSocket::SocketError socketError);
        void Connected();
        void HandleStateChange(QAbstractSocket::SocketState socketState);
        void MessageInterpreting(const std::map<std::string, std::string> data);

        void TakeStartWork(const std::map<std::string, std::string> data);

    private:        
        void Init();

        QTcpSocket *tcpSocket;
        enum state { WAITING, CONNECTED, ERROR} connection_state;
        QTimer *time;
        QString host;
        Peers::STATE state;
        int port;

        Board *board;
        unsigned int timeSteps;

};

#endif // WORKERTCP_H
