#include "SocketFileSender.h"


SocketFileSender::SocketFileSender(ClientParameters* params) :
    SocketClient(params)
{
}
    

SocketFileSender::~SocketFileSender()
{
}

bool SocketFileSender::SendFile(ClientParameters* params, const char* filePath)
{
    if (Connect(params) == -1) {
        return false;
    }

    std::string fileName = GetFileName(filePath);
    if (fileName == "") {
        puts("Cannot extract file name. Exiting...");
        return -1;
    }
    const int bufferSize = 256;
    SendString(fileName, bufferSize);

    SendFileData(filePath);
    
    return 1;    
}

std::string SocketFileSender::GetFileName(const char* fullPath)
{
    std::string fullPathStr(fullPath);
    // OS-specific code!
    unsigned int idx = fullPathStr.find_last_of("/");
    if (std::string::npos != idx) {
        std::string filename(fullPathStr.substr(idx + 1));
        return filename;
    }
    return "";
}

int SocketFileSender::SendFileData(const char* filePath)
{
    FileReader* reader = new FileReader(filePath);
    int fileSize = reader->GetFileSize();

    SendFileSize(fileSize);

    int bufferSize = 1024;
    char* buffer = new char[bufferSize];
    while (reader->CanRead()) {
        
        reader->GetData(buffer, bufferSize);
        
        SendBuffer(buffer, bufferSize);
        
        bufferSize = 1024;
        memset(buffer, 0, bufferSize);
    }

    puts("Data sending ended");
    delete [] buffer;
    delete reader;

    return 0;
}

int SocketFileSender::SendFileSize(int fileSize)
{
    StringToIntConverter converter;
    std::string sizeString = converter.ToString(fileSize);
    
    const int bufferSize = 256;
    SendString(sizeString, bufferSize);

    return 0;
}

int SocketFileSender::SendString(std::string& str, int size)
{
    
    char* stringBufer = new char[size];
    str.copy(stringBufer, str.length(), 0);

    SendBuffer(stringBufer, size);

    delete[] stringBufer;

    return 1;
}
