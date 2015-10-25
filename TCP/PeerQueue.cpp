#include "TCP/PeerQueue.h"

PeerQueue::PeerQueue()
{

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
