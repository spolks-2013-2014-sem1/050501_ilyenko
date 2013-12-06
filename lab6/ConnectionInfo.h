#ifndef __ConnectionInfo__
#define __ConnectionInfo__

#include "../lab3/FileWriter.h"

class ConnectionInfo {
public:
    FileWriter* writer;
    int fileSize;
    int bytesReceived;
};

#endif // __ConnectionInfo__