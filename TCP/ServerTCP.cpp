#include "TCP/ServerTCP.h"

ServerTCP::ServerTCP(QObject *parent) : QObject(parent)
{

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection));
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
    Traces() << "\n" << "LOG: Connection witch new client!";

    QTcpSocket * tempClientConnection;
    tempClientConnection = tcpServer->nextPendingConnection();
    clientConnection.push_back(tempClientConnection);
    connect(tempClientConnection,SIGNAL(readyRead()),this,SLOT(newDataFromClient()));
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
