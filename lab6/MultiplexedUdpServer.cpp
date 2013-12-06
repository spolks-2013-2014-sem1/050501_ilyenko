#include "MultiplexedUdpServer.h"

MultiplexedUdpServer::~MultiplexedUdpServer()
{
}


int 
MultiplexedUdpServer::StartServerCycle(int serverSocket, bool isTcp)
{
	sockaddr_in address;
    socklen_t addr_len = sizeof(sockaddr_in);    

    const int bufferSize = 1024;
    char buffer[bufferSize] = {0};

    while("true") {
        int bytesRead = recvfrom(serverSocket, buffer, bufferSize, 0, 
        	(sockaddr*)&address, &addr_len);

        if (bytesRead < 1) {
            perror("recvfrom");
            continue;
        }

        // Get clients' network address.
        long in_addr = address.sin_addr.s_addr; 

        if (clientAddresses.find(in_addr) == clientAddresses.end()) {

            FileWriter *writer = new FileWriter(buffer);
            int file_size = GetFileSize(serverSocket);

            ConnectionInfo *info = new ConnectionInfo();
            info->writer = writer;
            info->fileSize = file_size;
            info->bytesReceived = 0;
            clientAddresses[in_addr] = info;

        } else {
            FileWriter* writer = clientAddresses[in_addr]->writer;
            int fileSize = clientAddresses[in_addr]->fileSize;

            writer->WriteData(buffer, bytesRead);
            clientAddresses[in_addr]->bytesReceived += bytesRead;

            if (clientAddresses[in_addr]->bytesReceived >= fileSize) {
                printf("Total bytes received: %d\n", clientAddresses[in_addr]->bytesReceived);
                delete writer;
                delete clientAddresses[in_addr];
                clientAddresses.erase(in_addr);
            }
        }
    }
    return 1;
}