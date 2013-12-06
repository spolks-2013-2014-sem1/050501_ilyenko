#ifndef __FileReceiverWithUrgentData__
#define __FileReceiverWithUrgentData__ 

#include "../lab3/SocketFileReceiver.h"
#include <fcntl.h>

class FileReceiverWithUrgentData: public SocketFileReceiver
{
private:

    bool urgentFlag;

    char urgentData;

protected:

    int ReceiveFile(int socket);

    int CheckUrgentData(int socket);

    void UrgentOperation(int bytesRead, int bytesTotal);

    // Set socket ownership to get SIGURG when OOB data will be received.
    int SetSocketOwnership(int socket);

public:

    FileReceiverWithUrgentData();

    virtual ~FileReceiverWithUrgentData();

    // Re-define callback to track SIGURG
    void SignalCallback(int signum);

};

#endif //