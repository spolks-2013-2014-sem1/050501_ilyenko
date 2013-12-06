#include "MultiplexedServer.h"


MultiplexedServer::~MultiplexedServer()
{    
}

int
MultiplexedServer::StartServerCycle(int serverSocket, bool isTcp)
{

    int descTableSize = getdtablesize();

    fd_set sockets;
    fd_set socketsChanged;

    FD_ZERO(&sockets);
    FD_SET(serverSocket, &sockets);

    while("true") {

        memcpy(&socketsChanged, &sockets, sizeof(socketsChanged));
        if (select(descTableSize, &socketsChanged, 0, 0, 0) == -1 
            && errno != EINTR) {
            perror("select");
        }

        // Check if serverSocket is a part of "sockets_changed".
        if (FD_ISSET(serverSocket, &socketsChanged)) {
            int remoteSocket = AcceptClient(serverSocket);
            if (remoteSocket != -1) {
                // Add newly created connection to the set.
                FD_SET(remoteSocket, &sockets);
            }
        }

        for (int sock = 0; sock < descTableSize; ++sock) {
            if (sock != serverSocket && FD_ISSET(sock, &socketsChanged)) {
                if (ClientOperation(sock) == -1) {
                    puts("Error while receiving data.");
                }

                if (connectedSockets.find(sock) == connectedSockets.end()) {
                    // If we end operation and clean up a descriptor then
                    // remove it from fd_set too.
                    FD_CLR(sock, &sockets);
                }
            }
        }
    }

    return 1;
}

int
MultiplexedServer::AcceptClient(int serverSocket)
{
    int remote_socket = SocketServer::AcceptClient(serverSocket);

    if (remote_socket == -1) {
        return -1;
    }

    std::string fileName = GetFileName(remote_socket);
    FileWriter *writer = new FileWriter(fileName.c_str());
    int fileSize = GetFileSize(remote_socket);

    // Save info
    ConnectionInfo *info = new ConnectionInfo();
    info->writer = writer;
    info->fileSize = fileSize;
    info->bytesReceived = 0;
    connectedSockets[remote_socket] = info;

    // Allow catching URG signal
    SetSocketOwnership(remote_socket);
    
    return remote_socket;
}

int
MultiplexedServer::ClientOperation(int socket)
{
    FileWriter *writer = connectedSockets[socket]->writer;
    int fileSize = connectedSockets[socket]->fileSize;
    int bytesRead;

    const int bufferSize = 1024;
    char buffer[bufferSize] = {0};
    while ("true") {
        bytesRead = recv(socket, buffer, bufferSize, 0);
        
        int urgentCheck = CheckUrgentData(socket);
        if (urgentCheck == 1) {
            UrgentOperation(connectedSockets[socket]->bytesReceived, fileSize);
        }

        if (urgentCheck == 1 && bytesRead < 1) {
            continue;
        } else {
            break;
        }
    }

    if (bytesRead == -1) {
        return -1;
    }

    if (bytesRead > 0) {
        if (connectedSockets[socket]->bytesReceived + bytesRead > fileSize) {
            int bytesToWrite = fileSize - connectedSockets[socket]->bytesReceived ;
            writer->WriteData(buffer, bytesToWrite);
            connectedSockets[socket]->bytesReceived += bytesToWrite;            
        } else {
            writer->WriteData(buffer, bytesRead);
            connectedSockets[socket]->bytesReceived += bytesRead;
        }
    }

    if (connectedSockets[socket]->bytesReceived >= fileSize) {
        printf("Socket %d. Total received: %d\n bytes", socket, connectedSockets[socket]->bytesReceived);
        
        delete writer;
        Close(socket);

        delete connectedSockets[socket];
        connectedSockets.erase(socket);
    }

    return 0;
}