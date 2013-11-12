#include "SocketFileReceiver.h"

SocketFileReceiver::SocketFileReceiver()
{
}

SocketFileReceiver::~SocketFileReceiver()
{
}

int SocketFileReceiver::ClientOperation(int socket)
{
    return ReceiveFile(socket);
}

int SocketFileReceiver::ReceiveFile(int socket)
{
    const int bufferSize = 1024;

    std::string fileName = GetFileName(socket);
    FileWriter writer(fileName.c_str());

    int fileSize = GetFileSize(socket);

    char buffer[bufferSize] = {0};
    int totalBytesRead = 0;

    do {
        memset(buffer, 0, bufferSize);
        int bytesRead = recv(socket, buffer, bufferSize, 0);

        if (bytesRead > 0) {

            if (totalBytesRead + bytesRead > fileSize) {
                int bytesToWrite = fileSize - totalBytesRead;
                writer.WriteData(buffer, bytesToWrite);
                break;                    
            } else {
                writer.WriteData(buffer, bytesRead);
                totalBytesRead += bytesRead;                
            }
        } else {
            if (totalBytesRead != fileSize) {
                puts("Error when receiving file data.");    
            }
            break;
        }

    } while (totalBytesRead < fileSize);

    return 0;
}


std::string SocketFileReceiver::GetFileName(int socket)
{
    const int maxFileNameSize = 256;
    char* name = new char[maxFileNameSize];

    int recvResult = recv(socket, name, maxFileNameSize, 0);
    if (recvResult <= 0) {
        puts("Error when receiving the file name.");
        return NULL;
    }

    std::string result(name);
    delete[] name;

    return result;
}

int SocketFileReceiver::GetFileSize(int socket)
{
    // max ext4fs file size ~= 2^160 << 2^256 
    const int maxFileSizeLength = 256;
    char* fileSize = new char[maxFileSizeLength];

    int recvResult = recv(socket, fileSize, maxFileSizeLength, 0);
    if (recvResult <= 0) {
        puts("Error when receiving the file name.");
        return -1;
    } 

    StringToIntConverter converter;
    // to unsigned long
    int result = converter.ToInt(std::string(fileSize));

    return result;
}