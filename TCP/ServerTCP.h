#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Traces/Traces.h"

class ServerTCP : public QObject
{
    Q_OBJECT

    public:

    explicit ServerTCP(QObject *parent = 0);
    bool StartLisning(const QHostAddress&,quint16);
    ~ServerTCP();

    private slots:
        void newConnection();
        void newDataFromClient();

    private:
        QTcpServer *tcpServer;
        QList<QTcpSocket*> clientConnection;
};

#endif // SERVERTCP_H
