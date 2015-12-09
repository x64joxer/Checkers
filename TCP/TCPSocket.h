#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TCPSocket
{
    public:
        TCPSocket();

        void SetTcpSocketWsk(QTcpSocket * pointer) { wsk = pointer; }
        QTcpSocket * GetTcpSocketWsk() const { return wsk; }
        void SetDataWsk(char *wsk) { dataToRemove = wsk; }
        void DeleteData() { delete [] dataToRemove; dataToRemove = nullptr; }

        ~TCPSocket();

    private:
        QTcpSocket *wsk;
        char * dataToRemove;
};

#endif // TCPSOCKET_H
