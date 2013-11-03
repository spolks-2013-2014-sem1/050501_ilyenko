#include "SocketServer.h"
#include "SignalHandlerNotifier.h"

SocketServer::SocketServer(const char* addressString, const char* portString, const char* protocolName)
{
    SignalHandlerNotifier::Subscribe((ISignalObserver*)this);
    CreateServer(addressString, portString, protocolName);
}

SocketServer::SocketServer(const char* addressString, const char* portString, const char* protocolName, int outputDescriptor)
{
    SignalHandlerNotifier::Subscribe(this);
    this->outputDescriptor = outputDescriptor;
    CreateServer(addressString, portString, protocolName);
}

SocketServer::~SocketServer()
{
    CloseAllSockets();
}

int SocketServer::CreateServer(const char* addressString, const char* portString, const char* protocolName)
{
    int serverSocketDescriptor = CreateSocket(addressString, portString, protocolName);
    SetSocketOptions(serverSocketDescriptor);
    
    sockaddr_in socketAddress = CreateSocketAddress(portString);

    BindSocket(serverSocketDescriptor, (sockaddr*)&socketAddress);
    
    printf("Server started at %s:%s \n", addressString, portString);

    const int listenQueueLength = 10;
    StartListening(serverSocketDescriptor, listenQueueLength);
    StartServerCycle(serverSocketDescriptor);

    Close(serverSocketDescriptor);
    return 0;
}

int SocketServer::SetSocketOptions(int socketDescriptor)
{
    int option = 1;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (void*)&option, sizeof(option));

    return 0;
}

int SocketServer::StartServerCycle(int serverSocket)
{
    while("true") {
        int clientSocket = AcceptClient(serverSocket);
        if (clientSocket == -1) {
            continue;
        }

        ReadData(clientSocket);
        int shutdownResult = ShutdownSocket(clientSocket);
        if (shutdownResult == -1) {
            Close(serverSocket);
            exit(EXIT_FAILURE);
        }
        Close(clientSocket);
    }
    return 0;
}

int SocketServer::ReadData(int socket)
{
    const int bufferSize = 100;
    const char EOT = 04;
    char buffer[bufferSize] = {0};
    
    do {
        memset(buffer, 0, bufferSize);
        recv(socket, buffer, bufferSize, 0);
        write(this->outputDescriptor, buffer, GetDataLength(buffer, bufferSize));
    // Break receiveing when end-of-transmission character is found (Ctrl-D on UNIX).
    } while (strchr(buffer, EOT) == 0);

    return 0;
}

int SocketServer::GetDataLength(char* data, int maxLength)
{
    int result = maxLength;
    if (data[maxLength-1] == 0) {
        result = strlen(data);
    }
    return result;
}

int SocketServer::ShutdownSocket(int socket)
{
    int shutdownResult = shutdown(socket, SHUT_RDWR);
    if (shutdownResult == -1) {
        perror("Can not shutdown socket.");
        Close(socket);
    }
    return shutdownResult;
}

int SocketServer::AcceptClient(int serverSocket)
{
    int clientSocket = accept(serverSocket, 0, 0);

    if(clientSocket == -1) {
        perror("Error on client accept.");
        close(clientSocket);
    } else {
        openedSockets.push_back(clientSocket);
    }

    return clientSocket;
}

int SocketServer::StartListening(int socketDescriptor, int backlog)
{
    int listenResult = listen(socketDescriptor, backlog);
    if(listenResult == -1) {
        perror("Error while enabling the listen state.");
        Close(socketDescriptor);
        exit(EXIT_FAILURE);
    }
    return listenResult;
}

int SocketServer::BindSocket(int socketDescriptor, sockaddr* socketAddress)
{
    int bindResult = bind(socketDescriptor, socketAddress, sizeof(*socketAddress));
    
    if(bindResult == -1) {
        perror("Socket binding failed.");
        Close(socketDescriptor);
        exit(EXIT_FAILURE);
    }
    return bindResult;
}


int SocketServer::CreateSocket(const char* addressString, const char* portString, const char* protocolName)
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


sockaddr_in SocketServer::CreateSocketAddress(const char* portString)
{
    struct sockaddr_in socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(( unsigned short) atoi (portString));
    socketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Let's bind it to all interfaces!
    
    return socketAddress;
}

int SocketServer::DetermineSocketType(const char* protocolName)
{
    int type = SOCK_STREAM;
    if (strcmp( protocolName, "udp") == 0) {
        type = SOCK_DGRAM;
    } else if (strcmp( protocolName, "tcp") == 0) {
        type = SOCK_STREAM;
    }
    return type;
}

int SocketServer::Close(int socket)
{
    close(socket);
    openedSockets.pop_back();
    return 0;
}

void SocketServer::CloseAllSockets()
{
    for (unsigned int i = 0; i < openedSockets.size(); ++i) {
        Close(openedSockets[i]);
    }
}

void SocketServer::SignalCallback(int signum)
{
    CloseAllSockets();
    printf("Server halted after receiveing the signal %0d.\n", signum);
}