#include "TCP/PeerQueue.h"

PeerQueue::PeerQueue()
{
    server = NULL;
}

bool PeerQueue::PeerExist(QHostAddress ho, int po)
{
    bool flag = false;
    std::for_each(peers.begin(),peers.end(),
                  [&flag, ho, po](Peers &n){
                                 if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                 {
                                   Traces() << "\n" << "LOG: Peer exist in queue.";
                                   flag = true;
                                 };
                              });
    return flag;
}

void PeerQueue::AddPeer(QHostAddress ho, int po)
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    if (!PeerExist(ho,po))
    {
        Peers temp;
        temp.SetPeer(ho,po);
        peers.push_back(temp);
        Traces() << "\n" << "LOG: Peer added to queue.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer exist!";
    };
}

void PeerQueue::RemovePeer(QHostAddress ho, int po)
{
        std::lock_guard<std::mutex> guard(mutex_guard);

        Peers temp;
        bool flag = false;

        std::for_each(peers.begin(),peers.end(),
                      [&flag, &temp, ho, po](Peers &n){
                                     if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                     {
                                        temp = n;
                                        flag = true;
                                     };
                                     });

        if (flag)
        {
            peers.remove(temp);
            Traces() << "\n" << "LOG: Peer removed from queue.";
        } else
        {
            Traces() << "\n" << "ERROR: Peer not exist!";
        };
}

void PeerQueue::AddData(QHostAddress ho, int po,char *data)
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    Peers temp;
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, &temp, ho, po](Peers &n){
                                 if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                 {
                                    temp = n;
                                    flag = true;
                                 };
                                 });

    if (flag)
    {
        temp.AddData(data);
        Traces() << "\n" << "LOG: Data added to peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

void PeerQueue::GetData(QHostAddress ho, int po,char *data)
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    Peers temp;
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, &temp, ho, po](Peers &n){
                                 if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                 {
                                    temp = n;
                                    flag = true;
                                 };
                                 });

    if (flag)
    {
        temp.GetData(data);
        Traces() << "\n" << "LOG: Data transfered from peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

