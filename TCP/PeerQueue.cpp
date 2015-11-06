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
                                 if (!flag)
                                 {
                                     if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                     {
                                       Traces() << "\n" << "LOG: Peer exist in queue.";
                                       flag = true;
                                     }
                                 }
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

        bool flag = false;
        Peers *wsk;

        std::for_each(peers.begin(),peers.end(),
                      [&wsk, &flag, this, ho, po](Peers &n){
                                         if (!flag)
                                         {
                                             if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                             {
                                                wsk = &n;
                                                flag = true;
                                             }
                                         }
                                     });

        if (flag)
        {            
            peers.remove(*wsk);
            Traces() << "\n" << "LOG: Peer removed from queue.";
        } else
        {
            Traces() << "\n" << "ERROR: Peer not exist!";
        };
}

void PeerQueue::AddData(QHostAddress ho, int po,char *data)
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, this, data, ho, po](Peers &n){
                                     if (!flag)
                                     {
                                         if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                         {
                                            n.AddData(data);
                                            waitingMessages++;
                                            flag = true;
                                         }
                                     }
                                 });

    if (flag)
    {        
        Traces() << "\n" << "LOG: Data added to peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

void PeerQueue::GetData(QHostAddress ho, int po,char *data)
{    
    std::lock_guard<std::mutex> guard(mutex_guard);

    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, data, ho, po](Peers &n){
                                     if (!flag)
                                     {
                                         if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                         {
                                            n.GetData(data);
                                            flag = true;
                                         }
                                     }
                                 });

    if (flag)
    {        
        Traces() << "\n" << "LOG: Data transfered from peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

void PeerQueue::GetFirstMessage(QHostAddress &ho, int &po,char *data)
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, this, &data, &ho, &po](Peers &n){
                                        if (!flag)
                                        {
                                            if (n.IsData())
                                            {
                                                flag = true;
                                                n.GetData(data);
                                                ho = n.GetHost();
                                                po = n.GetPort();
                                                waitingMessages--;
                                            }
                                       }
                                 });
}

void PeerQueue::SetState(const QHostAddress ho, const int po, const Peers::STATE state)
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, state, ho, po](Peers &n){
                                     if (!flag)
                                     {
                                         if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                         {
                                            n.SetState(state);
                                            flag = true;
                                         }
                                     }
                                 });

    if (flag)
    {
        Traces() << "\n" << "LOG: State set";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}
