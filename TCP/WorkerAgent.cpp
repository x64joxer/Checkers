#include "TCP/WorkerAgent.h"

WorkerAgent::WorkerAgent(QObject *parent) : QObject(parent)
{

}

void WorkerAgent::Init()
{
    qRegisterMetaType<QHostAddress >("QHostAddress");

    messageForwarder.SetServer(&server);
    messageForwarder.SetPeerQueue(&peerQueue);    

    connect(&messageForwarder,SIGNAL(Send(QHostAddress,int,char*)),&server,SLOT(SendMessage(QHostAddress,int,char*)));

    server.SetPeerQueue(&peerQueue);
    server.StartLisning(QHostAddress::Any, ProgramVariables::GetServerPort());
}

void WorkerAgent::Stop()
{
    server.Stop();
}

PeerQueue  WorkerAgent::peerQueue;
MessageForwarder  WorkerAgent::messageForwarder;
ServerTCP WorkerAgent::server;
