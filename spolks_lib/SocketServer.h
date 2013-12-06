#ifndef __SocketServer__
#define __SocketServer__

#include "headers.h"
#include "ClientParameters.h"
#include "SocketBase.h"

class SocketServer: public SocketBase
{
private:
protected:
    
    int CreateServer(const char* addressString, 
        const char* portString, const char* protocolName);

    virtual int StartServerCycle(int serverSocket, bool isTcp);
    
    virtual int AcceptClient(int serverSocket);
    
    int StartListening(int socketDescriptor, int backlog);

    virtual int ClientOperation(int socket) = 0;

public:

    SocketServer();

    ~SocketServer();

    void Start(ClientParameters* params);

};

#endif //__SocketServer__