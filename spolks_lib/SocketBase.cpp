#include "SocketBase.h"

SocketBase::SocketBase()
{
    SignalHandlerNotifier::Subscribe((ISignalObserver*)this);
}

SocketBase::~SocketBase()
{
    CloseAllSockets();
}

int SocketBase::CreateSocket(const char* addressString, const char* portString, const char* protocolName)
{
    int socketType = DetermineSocketType(protocolName);
    
    protoent*  protocolEntry = getprotobyname(protocolName);
    
    int socketDescriptor = socket(PF_INET, socketType, protocolEntry->p_proto);
    
    if (socketDescriptor == -1) {
        exit(EXIT_FAILURE);
    }
    openedSockets.push_back(socketDescriptor);
    return socketDescriptor;
}


sockaddr_in SocketBase::CreateSocketAddress(const char* portString, 
    const char* address)
{
    struct sockaddr_in socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(( unsigned short) atoi (portString));
    if (address == 0) {
        socketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Let's bind it to all interfaces!
    } else {
        socketAddress.sin_addr.s_addr = inet_addr(address);
    }
        
    return socketAddress;
}

int SocketBase::BindSocket(int socketDescriptor, sockaddr* socketAddress)
{
    int bindResult = bind(socketDescriptor, socketAddress, sizeof(*socketAddress));
    
    if(bindResult == -1) {
        perror("Socket binding failed.");
        Close(socketDescriptor);
        exit(EXIT_FAILURE);
    }
    return bindResult;
}


int SocketBase::DetermineSocketType(const char* protocolName)
{
    int type = SOCK_STREAM;
    if (strcmp( protocolName, "udp") == 0) {
        type = SOCK_DGRAM;
    } else if (strcmp( protocolName, "tcp") == 0) {
        type = SOCK_STREAM;
    }
    return type;
}

int SocketBase::ShutdownSocket(int socket)
{
    int shutdownResult = shutdown(socket, SHUT_RDWR);
    if (shutdownResult == -1) {
        perror("Can not shutdown socket.");
        Close(socket);
    }
    return shutdownResult;
}

int SocketBase::Close(int socket)
{
    close(socket);
    openedSockets.pop_back();
    return 0;
}

int SocketBase::SetSocketOptions(int socketDescriptor)
{
    int option = 1;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (void*)&option, sizeof(option));

    return 0;
}

void SocketBase::CloseAllSockets()
{
    for (unsigned int i = 0; i < openedSockets.size(); ++i) {
        Close(openedSockets[i]);
    }
}

void SocketBase::SignalCallback(int signum)
{
    CloseAllSockets();
    printf("Socket was halted after receiving the signal %0d.\n", signum);
}