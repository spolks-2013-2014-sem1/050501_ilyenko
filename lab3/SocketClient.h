#ifndef __SocketClient__
#define __SocketClient__

#include "ClientParameters.h"
#include "SocketBase.h"

class SocketClient: public SocketBase
{
private:

    int GetLengthToSent(int bufferSize, int dataSize, int bytesSent);

protected:

    void CreateClient(ClientParameters* client);

    int SendData(const char* buffer, int bufferSize);

    int Connect(ClientParameters* server);

public:

    SocketClient(ClientParameters* params);
    
    virtual ~SocketClient();

    int SendTo(ClientParameters* server, const char* data,
        int dataSize);

};

#endif // __SocketClient__