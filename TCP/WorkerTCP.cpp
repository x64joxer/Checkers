#include "TCP/WorkerTCP.h"

WorkerTCP::WorkerTCP(QObject *parent)
          : QObject(parent),
            connection_state(DISCONNECTED),
            messageState(NONE_OK)
{
    Init(); 
}

void WorkerTCP::Init()
{
    globalData = new char[ProgramVariables::K4];
    globalLength = 0;
    state = Peers::STATE::FREE;
    board = new Board();

    time = new QTimer();
    connect(time,SIGNAL(timeout()),this,SLOT(Reconnect()));

    waitForOKMessageTimer = new QTimer();
    connect(waitForOKMessageTimer,SIGNAL(timeout()),this,SLOT(NoResponseFromServer()));
    waitForOKMessageTimer->setInterval(ProgramVariables::GetMaxTimeWaitToServer());

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadDataFromServer()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ConnectionError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(Connected()));

    waitForIATimer = new QTimer();
    waitForIATimer->setInterval(10);
    connect(waitForIATimer,SIGNAL(timeout()), this, SLOT(CheckStatus()));
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

    connection_state = CONNECTED;
    SendStateMessage();
}

void WorkerTCP::SendStateMessage()
{
    char * temp = new char[ProgramVariables::K4];
    MessageCoder::ClearChar(temp, ProgramVariables::K4);
    waitForOKMessageID = ProgramVariables::CreateMessageId();
    MessageCoder::CreateStateMessage(state, waitForOKMessageID, temp);

    while (tcpSocket->waitForBytesWritten()) {}
    waitForOKMessageTimer->start();
    messageState = STATE_OK;
    tcpSocket->write(temp);
    while (tcpSocket->waitForBytesWritten()) {}
    delete [] temp;
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
        connection_state = DISCONNECTED;
        break;
    default:
        Traces() << "\n" << "ERROR:The following error occurred:" << tcpSocket->errorString();
        connection_state = DISCONNECTED;
    }

    time->setInterval(ProgramVariables::GetRecconectingTime());
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
        connection_state = DISCONNECTED;
    };
}

void WorkerTCP::ReadDataFromServer()
{    

    if (globalLength == 0) MessageCoder::ClearChar(globalData, ProgramVariables::K4);

    unsigned int intTemp = tcpSocket->bytesAvailable();

    if (globalLength ==0)
    {
        tcpSocket->read(globalData, tcpSocket->bytesAvailable());
    } else
    {
        tcpSocket->read(globalData+globalLength, tcpSocket->bytesAvailable());
    }

    globalLength += intTemp;

    bool flag = false;

    unsigned int i = globalLength-10;

       if ((globalData[i] == 'G')&&
           (globalData[i+1] == 'E')&&
           (globalData[i+2] == '_')&&
           (globalData[i+3] == 'E')&&
           (globalData[i+4] == 'N')&&
           (globalData[i+5] == 'D'))
       {
           flag = true;
           globalLength = 0;   
       }    

    if (flag)
    {
        Traces() << "\n" << "LOG: New data from server: " << QString(globalData);

        std::map<std::string, std::string> recMessage;
        MessageCoder::MessageToMap(globalData, recMessage);

        MessageInterpreting(recMessage);
    }

}

void WorkerTCP::MessageInterpreting(const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: MessageHandler::MessageInterpreting(const std::map<std::string, std::string> data)";

    try
    {
        std::string action = data.at(MessageCoder::ACTION);

        if ((action != MessageCoder::OK)&&(messageState != NONE_OK))
        {
            Traces() << "\n" << "ERR: Expected OK message from server!";
        } else
        if (action == MessageCoder::START_WORK)
        {
            TakeStartWork(data);
        } else
        if (action == MessageCoder::OK)
        {
            if (messageState == NONE_OK)
            {
                Traces() << "\n" << "ERR: Unexpected OK message from server!";
            } else
            if (data.at(MessageCoder::MESSAGE_ID) != waitForOKMessageID)
            {
                Traces() << "\n" << "ERR: Unexpected OK message ID from server!";
            } else
            {
                waitForOKMessageTimer->stop();
                messageState = NONE_OK;
            }
        }
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error!";
    }
}

void WorkerTCP::TakeStartWork(const std::map<std::string, std::string> data)
{
    Traces() << "\n" << "LOG: WorkerTCP::TakeStartWork(const std::map<std::string, std::string> data)";

    try
    {            
            timeSteps = atoi(data.at(MessageCoder::MAX_TIME).c_str());
            jobId = data.at(MessageCoder::JOB_ID);
            MessageCoder::MapToBoard(data, board);

            Traces() << "\n" << "LOG: Board received:";
            board->printDebug();

            Traces() << "\n" << "LOG: ...witch origin:";
            board->GetOrigin().printDebug();


            endIaJobFlag = false;
            std::thread tempJob(&ThreadIAMove<900000>::operator (),
                                &jobExpander,
                                board,
                                &endIaJobFlag,
                                &currentPercentOfSteps,
                                ProgramVariables::GetNumberOfThreads(),
                                3000,
                                timeSteps,
                                KindOfSteps::Time);

            tempJob.detach();
            iaJob = std::move(tempJob);
            waitForIATimer->start();


            char *dest = new char[ProgramVariables::K4];
            MessageCoder::ClearChar(dest, ProgramVariables::K4);
            MessageCoder::CreateOkMessage(data.at(MessageCoder::MESSAGE_ID), dest);
            while (tcpSocket->waitForBytesWritten()) {}
            tcpSocket->write(dest);
            while (tcpSocket->waitForBytesWritten()) {}

            delete [] dest;        
    }
    catch (std::out_of_range)
    {
        Traces() << "\n" << "ERR: Protocol error!";
    }
}

void WorkerTCP::CheckStatus()
{
    if (endIaJobFlag)
    {

        if (connection_state == CONNECTED)
        {
            numOfReattempt = 0;
            SendBestResultMessage();
            waitForIATimer->stop();
            endIaJobFlag = false;
        } else
        {
            Traces() << "\n" << "LOG: Not conneted to server";
            waitForIATimer->stop();
            endIaJobFlag = false;
        }
    }
}

void WorkerTCP::SendBestResultMessage()
{
    Traces() << "\n" << "LOG: Sending best result";

    char * temp = new char[ProgramVariables::K4];

    MessageCoder::ClearChar(temp, ProgramVariables::K4);
    waitForOKMessageID = ProgramVariables::CreateMessageId();
    MessageCoder::CreateBestResultMessage(waitForOKMessageID, jobId, temp);
    MessageCoder::BoardToChar(*board, temp, 1);

    while (tcpSocket->waitForBytesWritten()) {}
    waitForOKMessageTimer->start();
    messageState = BEST_RESULT_OK;
    tcpSocket->write(temp);
    while (tcpSocket->waitForBytesWritten()) {}

    delete [] temp;
}

void WorkerTCP::NoResponseFromServer()
{
    waitForOKMessageTimer->stop();

    if (messageState == STATE_OK)
    {
        SendStateMessage();
    } else
    if (messageState == BEST_RESULT_OK)
    {
        if (numOfReattempt < ProgramVariables::GetMaxNumberOfReattempt())
        {
            numOfReattempt++;
            SendBestResultMessage();
        } else
        {
            Traces() << "\n" << "LOG: Reattempts BEST_RESUL exhusted!";
            messageState = NONE_OK;
        }
    }
}

WorkerTCP::~WorkerTCP()
{
    delete globalData;
    delete waitForOKMessageTimer;
    delete waitForIATimer;
    delete tcpSocket;
    delete board;
    delete time;
}
