#ifndef __SocketEchoServer__
#define __SocketEchoServer__

#include <stdio.h>
#include "../spolks_lib/SocketServer.h"


class SocketEchoServer: public SocketServer
{
private:
protected:
    
    FILE* outputDescriptor;

    int ReadData(int socket);
        
    int GetDataLength(char* data, int maxLength);

    int ClientOperation(int socket);

public:

    SocketEchoServer();

    ~SocketEchoServer();

    void Start(ClientParameters* params, FILE* outputDescriptor);

};

#endif //__SocketEchoServer__