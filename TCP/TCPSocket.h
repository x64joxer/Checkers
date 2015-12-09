#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Traces/Traces.h"

class TCPSocket : public QObject
{
       Q_OBJECT

    public:
        explicit TCPSocket(QObject *parent);

        void SetTcpSocketWsk(QTcpSocket * pointer) { wsk = pointer; }
        QTcpSocket * GetTcpSocketWsk() const { return wsk; }
        void SetDataWsk(char *wsk) { dataToRemove = wsk; }
        void DeleteData() { delete [] dataToRemove; dataToRemove = nullptr; }

        ~TCPSocket();

    signals:
        void NewData(QHostAddress ho, int po,char *data);

    public slots:
        void NewDataFromClient();

    private:
        QTcpSocket *wsk;
        char * dataToRemove;      
};

#endif // TCPSOCKET_H
