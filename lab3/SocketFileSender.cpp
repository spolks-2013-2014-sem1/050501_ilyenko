#include "SocketFileSender.h"


SocketFileSender::SocketFileSender(ClientParameters* params) :
    SocketClient(params)
{
}
    

SocketFileSender::~SocketFileSender()
{
}

bool SocketFileSender::SendFile(ClientParameters* params, 
    const char* filePath)
{
    if (Connect(params) == -1) {
        return false;
    }

    // refactor ?
    const char* fileName = GetFileName(filePath);
    SendBuffer(fileName, strlen(fileName));


    SendFileData(filePath);

    return false;    
}

const char* SocketFileSender::GetFileName(const char* fullPath)
{
    std::string fullPathStr(fullPath);
    // OS-specific
    const int idx = fullPathStr.find_last_of("/");
    if (std::string::npos != idx) {
        std::string filename(fullPathStr.substr(idx + 1));
        return filename.c_str();
    }
    return NULL;
}

int SocketFileSender::SendFileData(const char* filePath)
{
    FileReader reader(filePath);

    SendFileSize(reader.GetFileSize());

    int bufferSize = 100;
    char* buffer = new char[bufferSize];
    while (reader.CanRead()) {
        
        reader.GetData(buffer, bufferSize);
        SendBuffer(buffer, bufferSize);
        bufferSize = 100;
    
    }
    delete [] buffer;

    return 0;
}

int SocketFileSender::SendFileSize(int fileSize)
{
    StringToIntConverter converter;
    std::string sizeString = converter.ToString(fileSize);
    SendBuffer(sizeString.c_str(), sizeString.length());

    return 0;
}
