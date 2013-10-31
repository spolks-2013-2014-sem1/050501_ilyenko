#include "SocketServer.h"
#include "SignalHandlerNotifier.h"
#include "ClientParameters.h"
#include "SocketClient.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void ServerDemo();
void ClientDemo();


int main(int argc, char** argv)
{
    SignalHandlerNotifier::SetupSignalHandlers();

    if (argc == 2) {
    	if (strcmp(argv[1], "-server") == 0){
    		ServerDemo();
    	} else {
    		ClientDemo();
    	}
    }
    return EXIT_SUCCESS;
}

void ServerDemo()
{
	SocketServer server("127.0.0.1", "1441", "tcp");
}

void ClientDemo()
{
	ClientParameters clientConfig;
	clientConfig.ipAddress = "127.0.0.1";
	clientConfig.port = "1442";
	clientConfig.protocol = "tcp";

	SocketClient client(&clientConfig);

	ClientParameters serverConfig;
	serverConfig.ipAddress = "127.0.0.1";
	serverConfig.port = "1441";
	serverConfig.protocol = "tcp";

	const char* data = "some data to send";
	int dataSize = strlen(data);

	client.SendTo(&serverConfig, data, dataSize);
}