#ifndef __SocketFileSender__
#define __SocketFileSender__

#include "SocketClient.h"
#include "FileReader.h"
#include "StringToIntConverter.h"

class SocketFileSender: public SocketClient
{
private:

	const char* GetFileName(const char* fullPath);

protected:

	int SendFileData(const char* filePath);

	int SendFileSize(int fileSize);

public:

	SocketFileSender(ClientParameters* params);
    
    virtual ~SocketFileSender();

    bool SendFile(ClientParameters* params, const char* filePath);
};

#endif // __SocketFileSender__