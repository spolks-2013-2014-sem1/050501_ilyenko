#include "SocketClient.h"

SocketClient::SocketClient(ClientParameters* client)
{
    CreateClient(client);
}

SocketClient::~SocketClient()
{
    Close(this->socketDescriptor);
}

void SocketClient::CreateClient(ClientParameters* params)
{
    this->socketDescriptor = CreateSocket(params->ipAddress, params->port,
        params->protocol);
}

int SocketClient::SendBuffer(const char* buffer, int bufferSize)
{
    int bytesSent = send(this->socketDescriptor, buffer, bufferSize, 0);
    return bytesSent;
}

int SocketClient::Connect(ClientParameters* server)
{
    sockaddr_in serverAddress = CreateSocketAddress(server->port, 
        server->ipAddress);
    int connectResult = 
        connect(this->socketDescriptor, (struct sockaddr *)&serverAddress,
        sizeof(serverAddress));
    if (connectResult == -1) {
        perror("Connection was not established.");
    }
    return connectResult;
}

int SocketClient::SendTo(ClientParameters* server, const char* data,
    int dataSize)
{
    if (Connect(server) == -1) {
        // ERROR CODES ?
        return 1;
    }

    SendData(data, dataSize);
    
    ShutdownSocket(this->socketDescriptor);

    return 0;
}

int SocketClient::SendData(const char* data, int dataSize)
{
    const int bufferSize = 10;
    char* buffer = new char[bufferSize];
    int dataSent = 0;
    
    do {
        memset(buffer, 0, bufferSize);
        int lengthToSend = GetLengthToSend(bufferSize, dataSize, dataSent);
        memcpy(buffer, (char*)(data + dataSent), lengthToSend);
    
        dataSent += SendBuffer(buffer, lengthToSend);
    } while (dataSent < dataSize);

    delete [] buffer;

    return 0;
}

int SocketClient::GetLengthToSend(int bufferSize, int dataSize, int bytesSent)
{
    if (bytesSent + bufferSize > dataSize) {
        return dataSize - bytesSent;
    }   
    return bufferSize;
}