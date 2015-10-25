#ifndef PEERS_H
#define PEERS_H

#include <QHostAddress>

class Peers
{
    public:
        Peers();
        void SetPeer(QHostAddress ho, int po);
        QHostAddress GetHost();
        int GetPort();
        bool operator==(const Peers &);
    private:
        QHostAddress host;
        int port;
};

#endif // PEERS_H
