#include "TCP/ServerTCP.h"

ServerTCP::ServerTCP(QObject *parent) : QObject(parent)
{

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

bool ServerTCP::StartLisning(const QHostAddress&adress =QHostAddress::Any,quint16 port = 0)
{
    Traces() << "\n" << "LOG: Start lisening port:" << port;
    if (!tcpServer->listen(adress,port))
    {
        Traces() << "\n" << "LOG: Unable to start the server: " << tcpServer->errorString();
    }
}

void ServerTCP::newConnection()
{    
    QTcpSocket * tempClientConnection;
    tempClientConnection = tcpServer->nextPendingConnection();
    clientConnection.push_back(tempClientConnection);

    Traces() << "\n" << "LOG: Connection witch new client:" << tempClientConnection->peerAddress().toString() << ":" << tempClientConnection->peerPort();

    connect(tempClientConnection,SIGNAL(readyRead()),this,SLOT(newDataFromClient()));
    connect(tempClientConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));
    connect(tempClientConnection,SIGNAL(disconnected()),this,SLOT(Disconnected()));
}

void ServerTCP::ConnectionError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        Traces() << "\n" << "ERROR:The host was not found. Please check the host name and port settings";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        Traces() << "\n" << "LOG:The connection was refused by the peer" ;
        break;
    default:
        Traces() << "\n" << "ERROR:The following error occurred:";
    }
}

void ServerTCP::Disconnected()
{
    foreach (QTcpSocket *var, clientConnection)
    {
        if (var->state() == QAbstractSocket::UnconnectedState)
        {
            Traces() << "\n" << "ERROR: Worker disconnected :" << var->peerAddress().toString() << ":" << var->peerPort();
            clientConnection.removeOne(var);

            break;
        }
    }
}

void ServerTCP::newDataFromClient()
{
    char *data  = new char[100];

    foreach (QTcpSocket *var, clientConnection)
    {
        if (var->isReadable())
        {
            var->read(data,100);
            break;
        }
    }

    Traces() << "\n" << "LOG: Data from worker: " << QString(data);
    //DATA ANALYSE
    //ui->textReceiced->setText(QString(data));
    delete [] data;
}

ServerTCP::~ServerTCP()
{

}
