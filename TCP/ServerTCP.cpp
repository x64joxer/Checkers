#include "TCP/ServerTCP.h"

ServerTCP::ServerTCP(QObject *parent) : QObject(parent)
{
    peerQueue = NULL;    
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

void ServerTCP::SetPeerQueue(PeerQueue *peers)
{
    peerQueue = peers;
}

void ServerTCP::SendMessage(QHostAddress ho, int po, char* data)
{

    Traces() << "\n" << "SendMessage(QHostAddress ho, int po, char* data)";    

    foreach (QTcpSocket *var, clientConnection)
    {        
        if ((var->peerAddress() == ho)&&(var->peerPort() == po))
        {
            Traces() << "\n" << "LOG: Sending data to peer " << ho.toString() << ":" << po;            

            while(var->waitForBytesWritten()) {}
            var->write(data);
            while(var->waitForBytesWritten()) {}

            delete [] data;
            break;
        }
    }
}

void ServerTCP::newConnection()
{    
    QTcpSocket * tempClientConnection;
    tempClientConnection = tcpServer->nextPendingConnection();    
    Traces() << "\n" << "LOG: Connection witch new client:" << tempClientConnection->peerAddress().toString() << ":" << tempClientConnection->peerPort();
    clientConnection.push_back(tempClientConnection);    
    peerQueue->AddPeer(tempClientConnection->peerAddress(), tempClientConnection->peerPort());

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
            Traces() << "\n" << "LOG: Worker disconnected :" << var->peerAddress().toString() << ":" << var->peerPort();
            clientConnection.removeOne(var);
            peerQueue->RemovePeer(var->peerAddress(), var->peerPort());
            var->deleteLater();            
            break;
        }
    }
}

void ServerTCP::newDataFromClient()
{
    char *data  = new char[100];

    foreach (QTcpSocket *var, clientConnection)
    {
        if (var->bytesAvailable()>0)
        {                        
            var->read(data,var->bytesAvailable());
            Traces() << "\n" << "LOG: Data from worker " << var->peerAddress().toString() << ":" << var->peerPort() << ":" << QString(data);
            peerQueue->AddData(var->peerAddress(),var->peerPort(),data);
            break;
        }
    }

    delete [] data;
}

ServerTCP::~ServerTCP()
{

}
