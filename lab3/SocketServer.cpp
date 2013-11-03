#include "SocketServer.h"

SocketServer::SocketServer(const char* addressString, const char* portString, 
    const char* protocolName)
{
    this->outputDescriptor = stdout;
    CreateServer(addressString, portString, protocolName);
}

SocketServer::SocketServer(const char* addressString, const char* portString, 
    const char* protocolName, FILE* outputDescriptor)
{
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

int SocketServer::StartServerCycle(int serverSocket)
{
    while("true") {
        int clientSocket = AcceptClient(serverSocket);
        if (clientSocket == -1) {
            continue;
        }
        ////puts("Client connected.");
        ReadData(clientSocket);
        
        int shutdownResult = ShutdownSocket(clientSocket);
        if (shutdownResult == -1) {
            Close(serverSocket);
            Close(clientSocket);
            exit(EXIT_FAILURE);
        }
        
        Close(clientSocket);
        ////puts("Client connection has been closed.");
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
        int bytesRead = recv(socket, buffer, bufferSize, 0);
        
        if (bytesRead && bytesRead != -1) {
            fwrite(buffer, 1, GetDataLength(buffer, bufferSize), this->outputDescriptor);
            fflush(this->outputDescriptor);            
        } else {
            break;
        }
    // Break receiving when end-of-transmission character is found (Ctrl-D on UNIX).
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