#include "FileSenderWithUrgentData.h"
#include "FileReceiverWithUrgentData.h"
#include "../spolks_lib/SignalHandlerNotifier.h"

void ServerDemo();
void ClientDemo(char*);
void UsagePrompt();

int main(int argc, char** argv)
{
    SignalHandlerNotifier::SetupSignalHandlers();

    switch (argc) {
        case 2:
            if (!strcmp(argv[1], "-server")) {
                ServerDemo();
            } else {
                UsagePrompt();
            }
        break;
        case 3:
            if (!strcmp(argv[1], "-client")) {
                ClientDemo(argv[2]);
            } else {
                UsagePrompt();
            }
        break;
        default:
            UsagePrompt();
        break;
    }

    return EXIT_SUCCESS;    
}

void ServerDemo()
{
    ClientParameters params;
    params.ipAddress = "127.0.0.1";
    params.port = "1441";
    params.protocol = "tcp";

    FileReceiverWithUrgentData server;
    server.Start(&params);
}

void ClientDemo(char* path)
{
    ClientParameters clientConfig;
    clientConfig.ipAddress = "127.0.0.1";
    clientConfig.port = "1442";
    clientConfig.protocol = "tcp";

    FileSenderWithUrgentData client(&clientConfig);

    ClientParameters serverConfig;
    serverConfig.ipAddress = "127.0.0.1";
    serverConfig.port = "1441";
    serverConfig.protocol = "tcp";

    if (client.SendFile(&serverConfig, path) == 1) {
        puts("File sent");
    }
}

void UsagePrompt()
{
    puts("lab4 -server \n lab4 -client [path-to-file]");
}