#ifndef __MultiplexedServer__
#define __MultiplexedServer__

#include "../lab4/FileReceiverWithUrgentData.h"
#include "ConnectionInfo.h"


class MultiplexedServer: public FileReceiverWithUrgentData
{
private:

    std::map<int, ConnectionInfo*> connectedSockets;

protected:

    int StartServerCycle(int serverSocket, bool isTcp);

    int AcceptClient(int serverSocket);

    int ClientOperation(int socket);

public:

    virtual ~MultiplexedServer();

};

#endif // __MultiplexedServer__