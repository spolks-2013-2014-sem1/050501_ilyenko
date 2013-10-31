#include "SocketClient.h"

SocketClient::SocketClient(ClientParameters* client)
{
    CreateClient(client);
}

SocketClient::~SocketClient()
{
}

void SocketClient::CreateClient(ClientParameters* params)
{
    this->socketDescriptor = CreateSocket(params->ipAddress, params->port,
        params->protocol);
}

int SocketClient::SendData(const char* buffer, int bufferSize)
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
    Connect(server);

    const int bufferSize = 100;
    char* buffer = new char[bufferSize];
    int dataSent = 0;

    do {
        memset(buffer, 0, bufferSize);
        int lengthToSend = GetLengthToSent(bufferSize, dataSize, dataSent);
        memcpy(buffer, (data + dataSent), lengthToSend);
        dataSent += SendData(buffer, lengthToSend);
    } while (dataSent < dataSize);

    delete [] buffer; 
    return 0;
}

int SocketClient::GetLengthToSent(int bufferSize, int dataSize, int bytesSent)
{
    if (bytesSent + bufferSize > dataSize) {
        return dataSize - bytesSent;
    }   
    return bufferSize;
}