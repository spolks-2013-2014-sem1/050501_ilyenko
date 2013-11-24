#include "FileReceiverWithUrgentData.h"


FileReceiverWithUrgentData::
FileReceiverWithUrgentData()
{
    // Set up additional signal handler to track urgent data
    SignalHandlerNotifier::Subscribe((ISignalObserver *)this, SIGURG);
    this->urgentFlag = false;
}


FileReceiverWithUrgentData::
~FileReceiverWithUrgentData()
{
}

void 
FileReceiverWithUrgentData::
SignalCallback(int signum)
{
    if (signum == SIGURG) {
        this->urgentFlag = true;
    } else {
        SocketBase::SignalCallback(signum);
    }
}



int 
FileReceiverWithUrgentData::
ReceiveFile(int socket)
{
    const int bufferSize = 1024;

    std::string fileName = GetFileName(socket);
    FileWriter writer(fileName.c_str());

    int fileSize = GetFileSize(socket);

    char buffer[bufferSize] = {0};
    int totalBytesRead = 0;

    do {

        if (CheckUrgentData(socket) == 1) {
            UrgentOperation(totalBytesRead, fileSize);
        }

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

int 
FileReceiverWithUrgentData::
CheckUrgentData(int socket)
{
    if (this->urgentFlag) {
        int mark = sockatmark(socket);
        if (mark == -1) {
            perror("sockatmark check failed:");
        } else if (mark) {
            if (recv(socket, &this->urgentData, 1, MSG_OOB) <= 0) {
                perror("OOB data receiving failed:");
            }
        }
        return mark;
    }
    return 0;
}


void 
FileReceiverWithUrgentData::
UrgentOperation(int bytesRead, int bytesTotal)
{
    int percent = bytesRead/bytesTotal;
    printf("\n[%d%%] Received %d/%d\n", percent, bytesRead, bytesTotal);
}