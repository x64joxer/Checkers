#ifndef WORKERTCP_H
#define WORKERTCP_H

#include <QTcpSocket>
#include <QTcpServer>
#include "Traces/Traces.h"

class WorkerTCP : public QObject
{
    Q_OBJECT

    public:
        explicit WorkerTCP(QObject *parent = 0);
        ~WorkerTCP();

        void ConnectToServer(const QString host, unsigned int port);

    signals:

    public slots:
        void ReadDataFromServer();
        void ConnectionError(QAbstractSocket::SocketError socketError);

    private:
        QTcpSocket *tcpSocket;
};

#endif // WORKERTCP_H
