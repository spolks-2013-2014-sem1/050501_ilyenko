#ifndef __SocketFileReceiver__
#define __SocketFileReceiver__

#include "../spolks_lib/SocketServer.h"
#include "../spolks_lib/ClientParameters.h"
#include "../spolks_lib/StringToIntConverter.h"
#include "FileWriter.h"


class SocketFileReceiver : public SocketServer
{
private:
protected:

    virtual int ReceiveFile(int socket); 
    
    std::string GetFileName(int socket);

    int GetFileSize(int socket);

    int ClientOperation(int socket);

public:
    
    SocketFileReceiver();

    ~SocketFileReceiver();
};

#endif // __SocketFileReceiver__