#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Traces/Traces.h"
#include "TCP/PeerQueue.h"

class PeerQueue;

class ServerTCP : public QObject
{
    Q_OBJECT

    public:

    explicit ServerTCP(QObject *parent = 0);
    void Stop();
    bool StartLisning(const QHostAddress&,quint16);
    void SetPeerQueue(PeerQueue *peers);    
    ~ServerTCP();

    public slots:
        void SendMessage(QHostAddress ho, int po, char* data);

    private slots:
        void newConnection();
        void newDataFromClient();
        void ConnectionError(QAbstractSocket::SocketError socketError);
        void Disconnected();


    private:
        QTcpServer *tcpServer;
        QList<QTcpSocket*> clientConnection;        
        PeerQueue *peerQueue;
};

#endif // SERVERTCP_H
