#include "SocketEchoServer.h"

SocketEchoServer::SocketEchoServer(){}

SocketEchoServer::~SocketEchoServer(){}

void SocketEchoServer::Start(ClientParameters* params, FILE* outputDescriptor)
{
	this->outputDescriptor = outputDescriptor;
	SocketServer::Start(params);
}

int SocketEchoServer::ClientOperation(int socket)
{
    return ReadData(socket);
}

int SocketEchoServer::ReadData(int socket)
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

int SocketEchoServer::GetDataLength(char* data, int maxLength)
{
    int result = maxLength;
    if (data[maxLength-1] == 0) {
        result = strlen(data);
    }
    return result;
}
