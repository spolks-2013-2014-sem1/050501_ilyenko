#ifndef __SocketServer__
#define __SocketServer__

#include "headers.h"
#include "ISignalObserver.h"

class SocketServer: public ISignalObserver
{
private:
public:

    SocketServer(const char* addressString, const char* portString, const char* protocolName);

    SocketServer(const char* addressString, const char* portString, const char* protocolName, int outputDescriptor);

    ~SocketServer();

    void SignalCallback(int signum);

protected:
    
    std::vector<int> openedSockets;
    
    int outputDescriptor;


    int CreateServer(const char* addressString, const char* portString, const char* protocolName);

    int StartServerCycle(int serverSocket);
    
    int ReadData(int socket);
    
    int ShutdownSocket(int socket);
    
    int BindSocket(int socketDescriptor, sockaddr* socketAddress);
    
    int CreateSocket(const char* addressString,  const char* portString, const char* protocolName);
    
    int DetermineSocketType(const char* protocolName);
    
    int AcceptClient(int serverSocket);
    
    int StartListening(int socketDescriptor, int backlog);
    
    int SetSocketOptions(int socketDescriptor);
    
    void SetupSignalHandlers();
    
    sockaddr_in CreateSocketAddress(const char* portString);
    
    int Close(int socket);
    
    void CloseAllSockets();
    
    int GetDataLength(char* data, int maxLength);

};

#endif //__SocketServer__