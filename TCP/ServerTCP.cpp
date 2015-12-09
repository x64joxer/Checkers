#include "TCP/ServerTCP.h"

ServerTCP::ServerTCP(QObject *parent) : QObject(parent)
{
    peerQueue = NULL;    
    tcpServer = new QTcpServer(this);    
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void ServerTCP::Stop()
{
    foreach (TCPSocket *var, clientConnection)
    {
        var->GetTcpSocketWsk()->close();
    }

    tcpServer->close();
}

bool ServerTCP::StartLisning(const QHostAddress&adress =QHostAddress::Any,quint16 port = 0)
{
    TRACE01 Traces() << "\n" << "LOG: Start lisening port:" << port;

    if (!tcpServer->listen(adress,port))
    {
        TRACE01 Traces() << "\n" << "LOG: Unable to start the server: " << tcpServer->errorString();
        return 1;
    }

    return 0;
}

void ServerTCP::SetPeerQueue(PeerQueue *peers)
{
    peerQueue = peers;
}

void ServerTCP::SendMessage(QHostAddress ho, int po, char* data)
{

    TRACE01 Traces() << "\n" << "LOG: SendMessage(QHostAddress ho, int po, char* data)";

    foreach (TCPSocket *var, clientConnection)
    {        
        if ((var->GetTcpSocketWsk()->peerAddress() == ho)&&(var->GetTcpSocketWsk()->peerPort() == po))
        {
            TRACE01 Traces() << "\n" << "LOG: Sending data to peer " << ho.toString() << ":" << po;            

            while(var->GetTcpSocketWsk()->waitForBytesWritten()) {}
            var->DeleteData();
            var->SetDataWsk(data);
            var->GetTcpSocketWsk()->write(data);

            break;
        }
    }
}

void ServerTCP::newConnection()
{    
    TCPSocket * tempClientConnection = new TCPSocket(this);
    tempClientConnection->SetTcpSocketWsk(tcpServer->nextPendingConnection());
    TRACE01 Traces() << "\n" << "LOG: Connection witch new client:" << tempClientConnection->GetTcpSocketWsk()->peerAddress().toString() << ":" << tempClientConnection->GetTcpSocketWsk()->peerPort();
    clientConnection.push_back(tempClientConnection);    
    peerQueue->AddPeer(tempClientConnection->GetTcpSocketWsk()->peerAddress(), tempClientConnection->GetTcpSocketWsk()->peerPort());

    connect(tempClientConnection->GetTcpSocketWsk(),SIGNAL(readyRead()),tempClientConnection,SLOT(NewDataFromClient()));
    connect(tempClientConnection->GetTcpSocketWsk(),SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));
    connect(tempClientConnection->GetTcpSocketWsk(),SIGNAL(disconnected()),this,SLOT(Disconnected()));
    connect(tempClientConnection, SIGNAL(NewData(QHostAddress,int,char*)), this, SLOT(newDataFromClient(QHostAddress,int,char*)));
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
        TRACE01 Traces() << "\n" << "LOG:The connection was refused by the peer" ;
        break;
    default:
        Traces() << "\n" << "ERROR:The following error occurred:";
    }
}

void ServerTCP::Disconnected()
{
    foreach (TCPSocket *var, clientConnection)
    {
        if (var->GetTcpSocketWsk()->state() == QAbstractSocket::UnconnectedState)
        {
            TRACE01 Traces() << "\n" << "LOG: Worker disconnected :" << var->GetTcpSocketWsk()->peerAddress().toString() << ":" << var->GetTcpSocketWsk()->peerPort();
            clientConnection.removeOne(var);
            peerQueue->RemovePeer(var->GetTcpSocketWsk()->peerAddress(), var->GetTcpSocketWsk()->peerPort());
            delete var;
            break;
        }
    }
}

void ServerTCP::newDataFromClient(QHostAddress ho, int po, char* data)
{  
    peerQueue->AddData(ho, po,data);
}

ServerTCP::~ServerTCP()
{       
    delete tcpServer;
}
