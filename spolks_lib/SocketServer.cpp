#include "SocketServer.h"

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
    CloseAllSockets();
}

void SocketServer::Start(ClientParameters* params)
{
    CreateServer(params->ipAddress, params->port, 
        params->protocol);
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
        puts("Client connected.");
        
        ClientOperation(clientSocket);
        
        int shutdownResult = ShutdownSocket(clientSocket);
        if (shutdownResult == -1) {
            Close(serverSocket);
            Close(clientSocket);
            exit(EXIT_FAILURE);
        }
        
        Close(clientSocket);
        puts("Client connection has been closed.");
    }
    return 0;
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