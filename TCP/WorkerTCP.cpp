#include "TCP/WorkerTCP.h"

WorkerTCP::WorkerTCP(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadDataFromServer()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));
}

void WorkerTCP::ConnectToServer(const QString host, unsigned int port)
{
    Traces() << "\n" << "LOG: Connecting to host:" << host << " port:" << port;
    tcpSocket->connectToHost(host,port);
}

void WorkerTCP::ConnectionError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        Traces() << "\n" << "ERROR:The host was not found. Please check the host name and port settings";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        Traces() << "\n" << "ERROR:The connection was refused by the peer" ;
        break;
    default:
        Traces() << "\n" << "ERROR:The following error occurred:" << tcpSocket->errorString();
    }

}

void WorkerTCP::ReadDataFromServer()
{
    char *data  = new char[100];
    tcpSocket->read(data,100);

    //ui->textReceived->setText(QString(data));
    delete [] data;
}

WorkerTCP::~WorkerTCP()
{
    delete tcpSocket;
}
