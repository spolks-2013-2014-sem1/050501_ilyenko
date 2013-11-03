#ifndef __SocketServer__
#define __SocketServer__

#include "headers.h"

#include <stdio.h>
#include "SocketBase.h"

class SocketServer: public SocketBase
{
private:
protected:
    
    FILE* outputDescriptor;


    int CreateServer(const char* addressString, 
        const char* portString, const char* protocolName);

    int StartServerCycle(int serverSocket);
    
    int ReadData(int socket);
    
    int AcceptClient(int serverSocket);
    
    int StartListening(int socketDescriptor, int backlog);
    
    int GetDataLength(char* data, int maxLength);

public:

    SocketServer(const char* addressString, const char* portString, 
        const char* protocolName);

    SocketServer(const char* addressString, const char* portString, 
        const char* protocolName, FILE* outputDescriptor);

    ~SocketServer();

};

#endif //__SocketServer__