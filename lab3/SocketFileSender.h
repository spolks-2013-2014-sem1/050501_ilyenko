#ifndef __SocketFileSender__
#define __SocketFileSender__

#include "../spolks_lib/SocketClient.h"
#include "../spolks_lib/StringToIntConverter.h"
#include "FileReader.h"


class SocketFileSender: public SocketClient
{
private:

    std::string GetFileName(const char* fullPath);

    int SendString(std::string& str, int bufferSize);

protected:

    int SendFileData(const char* filePath);

    int SendFileSize(int fileSize);

    int SendFileName(std::string& fileName);

public:

    SocketFileSender(ClientParameters* params);
    
    virtual ~SocketFileSender();

    bool SendFile(ClientParameters* params, const char* filePath);
};

#endif // __SocketFileSender__