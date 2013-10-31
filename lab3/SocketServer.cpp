#include "SocketServer.h"

SocketServer::SocketServer(const char* addressString, const char* portString, const char* protocolName)
{
    CreateServer(addressString, portString, protocolName);
}

SocketServer::SocketServer(const char* addressString, const char* portString, const char* protocolName, int outputDescriptor)
{
    SignalHandlerNotifier::Subscribe(this);
    CreateServer(addressString, portString, protocolName);
    this->outputDescriptor = outputDescriptor;
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