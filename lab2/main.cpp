#include "SocketEchoServer.h"
#include "../spolks_lib/SignalHandlerNotifier.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    SignalHandlerNotifier::SetupSignalHandlers();

    ClientParameters params;
    params.ipAddress = "127.0.0.1";
    params.port = "1441";
    params.protocol = "tcp";

    SocketEchoServer server;
    server.Start(&params, stdout);
    
    return EXIT_SUCCESS;
}