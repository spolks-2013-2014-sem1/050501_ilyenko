#ifndef __MultiplexedUdpServer__
#define __MultiplexedUdpServer__

#include "../lab4/FileReceiverWithUrgentData.h"
#include "ConnectionInfo.h"


class MultiplexedUdpServer: public FileReceiverWithUrgentData
{
private:

    std::map<long, ConnectionInfo*> clientAddresses;

protected:

    int StartServerCycle(int serverSocket, bool isTcp);

public:

    virtual ~MultiplexedUdpServer();

};

#endif // __MultiplexedUdpServer__