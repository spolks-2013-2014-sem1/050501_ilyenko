#ifndef __FileSenderWithUrgetnData__
#define __FileSenderWithUrgetnData__

#include "../lab3/SocketFileSender.h"


class FileSenderWithUrgentData: public SocketFileSender
{
private:

protected:

    void SendUrgentData();

public:

    FileSenderWithUrgentData(ClientParameters* params);

    virtual ~FileSenderWithUrgentData();

    int SendFileData(const char* filePath);

};

#endif //__FileSenderWithUrgetnData__