#include "../lab3/SocketFileReceiver.h"


class FileReceiverWithUrgentData: public SocketFileReceiver
{
private:

    bool urgentFlag;

    char urgentData;

protected:

    int ReceiveFile(int socket);

    int CheckUrgentData(int socket);

    void UrgentOperation(int bytesRead, int bytesTotal);

public:

    FileReceiverWithUrgentData();

    virtual ~FileReceiverWithUrgentData();

    // Re-define callback to track SIGURG
    void SignalCallback(int signum);

};