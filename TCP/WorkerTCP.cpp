#include "TCP/WorkerTCP.h"

WorkerTCP::WorkerTCP(QObject *parent) : QObject(parent)
{
    time = new QTimer();
    connect(time,SIGNAL(timeout()),this,SLOT(Reconnect()));

    tcpSocket = new QTcpSocket(this);    
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadDataFromServer()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));       
    connect(tcpSocket, SIGNAL(stateChanged(AbstractSocket::SocketState)), this, SLOT(HandleStateChange(AbstractSocket::SocketState)));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(Connected()));
}

void WorkerTCP::ConnectToServer(const QString ho,  int po)
{    
    host = ho;
    port = po;

    Traces() << "\n" << "LOG: Connecting to host:" << host << " port:" << port;
    tcpSocket->connectToHost(host,port);
}

void WorkerTCP::Reconnect()
{
    time->stop();
    Traces() << "\n" << "LOG: Reconnecting to host:"  << host << " port:" << port;;
    tcpSocket->connectToHost(host,port);
}

void WorkerTCP::Connected()
{
    Traces() << "\n" << "LOG: SUCCES! Connected to host:"  << host << " port:" << port;;

    char * temp = "czesc";
    tcpSocket->write(temp);
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

    time->setInterval(5000);
    time->start();
}

void WorkerTCP::HandleStateChange(QAbstractSocket::SocketState socketState)
{
    Traces() << "\n" << "LOG: Connection state changes";

    if (socketState == QAbstractSocket::ConnectedState)
    {
        connection_state = CONNECTED;
    } else
    {
        connection_state = ERROR;
    };
}

void WorkerTCP::ReadDataFromServer()
{
    Traces() << "\n" << "LOG: New data from server";
    char *data  = new char[100];
    tcpSocket->read(data,100);

    delete [] data;
}

WorkerTCP::~WorkerTCP()
{
    delete tcpSocket;
    delete time;
}
