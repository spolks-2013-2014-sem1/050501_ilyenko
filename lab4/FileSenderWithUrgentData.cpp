#include "FileSenderWithUrgentData.h"


FileSenderWithUrgentData::
FileSenderWithUrgentData(ClientParameters* params) : SocketFileSender(params)
{
}


FileSenderWithUrgentData::
~FileSenderWithUrgentData()
{
}


void FileSenderWithUrgentData::SendUrgentData()
{
    char data[1] = {1};
    send(this->socketDescriptor, data, 1, MSG_OOB);    
}


int
FileSenderWithUrgentData::
SendFileData(const char* filePath)
{
    FileReader* reader = new FileReader(filePath);
    int fileSize = reader->GetFileSize();

    SendFileSize(fileSize);

    int bufferSize = 1024;
    char* buffer = new char[bufferSize];

    int bufferNumSent = 0;
    SendUrgentData();

    while (reader->CanRead()) {
                
        reader->GetData(buffer, bufferSize);
        
        SendBuffer(buffer, bufferSize);
        
        bufferSize = 1024;
        memset(buffer, 0, bufferSize);

        ++bufferNumSent;
        if (bufferNumSent % 5 == 0) {
            SendUrgentData();
        }
    }

    SendUrgentData();

    puts("Data sending ended");
    delete [] buffer;
    delete reader;

    return 0;
}