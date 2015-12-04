#include "TCP/PeerQueue.h"

PeerQueue::PeerQueue()
          : freePeers(0),
            busyPeers(0)
{
    condition_var = ProgramVariables::GetGlobalConditionVariable();
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
                                       TRACE01 Traces() << "\n" << "LOG: Peer exist in queue.";
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
        ProgramVariables::NotifyOne();

        TRACE01 Traces() << "\n" << "LOG: Peer added to queue.";
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
                                                if (n.GetState() == Peers::STATE::FREE)
                                                {
                                                    --freePeers;
                                                } else
                                                if (n.GetState() == Peers::STATE::FREE)
                                                {
                                                    --busyPeers;
                                                }
                                                flag = true;
                                             }
                                         }
                                     });

        if (flag)
        {
            if (waitingMessages > 0) waitingMessages -= wsk->NumberOfMessages();
            messagesQueue.remove(wsk);
            peers.remove(*wsk);            
            ProgramVariables::NotifyOne();

            TRACE01 Traces() << "\n" << "LOG: Peer removed from queue.";
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
                                            messagesQueue.push_back(&n);
                                            waitingMessages++;
                                            flag = true;
                                         }
                                     }
                                 });

    if (flag)
    {        
        ProgramVariables::NotifyOne();

        TRACE01 Traces() << "\n" << "LOG: Data added to peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

Peers PeerQueue::AT(const unsigned int n)
{
    unsigned int counter = 0;
    Peers *tmp;

    if (peers.size() >= n)
    {
        std::for_each(peers.begin(),peers.end(),
                      [&tmp, n, &counter](Peers &var){
                                    if (n == counter)
                                    {
                                        tmp = &var;
                                    }
                                    counter++;
                                  });
    }

   return *tmp;
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
        TRACE01 Traces() << "\n" << "LOG: Data transfered from peer.";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}

void PeerQueue::GetFirstMessage(QHostAddress &ho, int &po,char *data)
{
    std::lock_guard<std::mutex> guard(mutex_guard);

    if (!messagesQueue.empty())
    {
        Peers *wsk = messagesQueue.front();
        wsk->GetData(data);
        ho = wsk->GetHost();
        po = wsk->GetPort();
        waitingMessages--;
        messagesQueue.pop_front();
    } else
    {
        Traces() << "\n" << "ERROR: No messges in message queue!";
    }
}

void PeerQueue::GetFirstFreePeers(QHostAddress &ho, int &po)
{
    TRACE01 Traces() << "\n" << "LOG: PeerQueue::GetFirstFreePeers(QHostAddress &ho, int &po)";

    std::lock_guard<std::mutex> guard(mutex_guard);
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, this, &ho, &po](Peers &n){
                                        if (!flag)
                                        {
                                            if (n.GetState() == Peers::STATE::FREE)
                                            {
                                                flag = true;
                                                ho = n.GetHost();
                                                po = n.GetPort();
                                            }
                                       }
                                 });
}

unsigned int PeerQueue::GetFreeStateNumber()
{    
    std::lock_guard<std::mutex> guard(mutex_guard);
    return freePeers;
}

unsigned int PeerQueue::GetBusyStateNumber()
{
    std::lock_guard<std::mutex> guard(mutex_guard);
    return busyPeers;
}

void PeerQueue::SetState(const QHostAddress ho, const int po, const Peers::STATE state)
{
    TRACE01 Traces() << "\n" << "LOG: PeerQueue::SetState(const QHostAddress ho, const int po, const Peers::STATE state)";

    std::lock_guard<std::mutex> guard(mutex_guard);
    bool flag = false;

    std::for_each(peers.begin(),peers.end(),
                  [&flag, this, state, ho, po](Peers &n){
                                     if (!flag)
                                     {
                                         if ((n.GetHost() == ho)&&(n.GetPort() == po))
                                         {
                                            if (state == Peers::STATE::FREE)
                                            {
                                                if (n.GetState() != Peers::STATE::FREE) freePeers++;
                                            } else
                                            {
                                                if (n.GetState() == Peers::STATE::FREE) freePeers--;
                                            }
                                            if (state == Peers::STATE::BUSY)
                                            {
                                                if (n.GetState() != Peers::STATE::BUSY) busyPeers++;
                                            } else
                                            {
                                                if (n.GetState() == Peers::STATE::BUSY) busyPeers--;
                                            }

                                            n.SetState(state);

                                            flag = true;                                            
                                         }
                                     }
                                 });

    if (flag)        
    {
        ProgramVariables::NotifyOne();

        TRACE01 Traces() << "\n" << "LOG: State set";
    } else
    {
        Traces() << "\n" << "ERROR: Peer not exist!";
    };
}
