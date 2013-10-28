#include "SocketServer.h"
#include "SignalHandlerObserver.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    SignalHandlerObserver::SetupSignalHandlers();
    SocketServer server("127.0.0.1", "1441", "tcp");
    return EXIT_SUCCESS;
}