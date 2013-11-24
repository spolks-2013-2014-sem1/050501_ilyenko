#ifndef __SocketBase__
#define __SocketBase__

#include "headers.h"

#include <netinet/in.h>
#include <arpa/inet.h>

#include "ISignalObserver.h"
#include "SignalHandlerNotifier.h"

class SocketBase: public ISignalObserver
{
private:
protected:

    int socketDescriptor;

    std::vector<int> openedSockets;


    int CreateSocket(const char* addressString,  
        const char* portString, const char* protocolName);

    sockaddr_in CreateSocketAddress(const char* portString,
        const char* address = 0);

    int ShutdownSocket(int socket);
    
    int BindSocket(int socketDescriptor, sockaddr* socketAddress);
    
    int DetermineSocketType(const char* protocolName);
    
    int SetSocketOptions(int socketDescriptor);
    
    int Close(int socket);
    
    void CloseAllSockets();

public:

    SocketBase();

    ~SocketBase();

    void SignalCallback(int signum);

};

#endif //__SocketBase__