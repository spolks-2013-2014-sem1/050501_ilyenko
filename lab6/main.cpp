#include "../spolks_lib/SignalHandlerNotifier.h"
#include "MultiplexedServer.h"
#include "MultiplexedUdpServer.h"
#include "../lab4/FileSenderWithUrgentData.h"

void ServerDemo(char*);
void ClientDemo(char*, char*);
void UsagePrompt();

int main(int argc, char** argv)
{
    SignalHandlerNotifier::SetupSignalHandlers();

    switch (argc) {
        case 3:
            if (!strcmp(argv[1], "-server")) {
                ServerDemo(argv[2]);
            } else {
                UsagePrompt();
            }
        break;
        case 4:
            if (!strcmp(argv[1], "-client")) {
                ClientDemo(argv[3], argv[2]);
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

void ServerDemo(char* tcpUdp)
{
    ClientParameters params;
    params.ipAddress = "127.0.0.1";
    params.port = "1441";
    
    if (!strcmp(tcpUdp, "TCP")) {
        params.protocol = "tcp";    
        MultiplexedServer server = MultiplexedServer();
        server.Start(&params);
    } else if (!strcmp(tcpUdp, "UDP")) {
        params.protocol = "udp";    
        MultiplexedUdpServer server = MultiplexedUdpServer();
        server.Start(&params);
    }
}

void ClientDemo(char* path, char* tcpUdp)
{
    ClientParameters clientConfig;
    clientConfig.ipAddress = "127.0.0.1";
    clientConfig.port = "1442";

    if (!strcmp(tcpUdp, "TCP")) {
        clientConfig.protocol = "tcp";    
    } else if (!strcmp(tcpUdp, "UDP")) {
        clientConfig.protocol = "udp";    
    }    


    ClientParameters serverConfig;
    serverConfig.ipAddress = "127.0.0.1";
    serverConfig.port = "1441";

    puts(tcpUdp);

    if (!strcmp(tcpUdp, "TCP")) {
        serverConfig.protocol = "tcp";
        FileSenderWithUrgentData client(&clientConfig);
        if (client.SendFile(&serverConfig, path) == 1) {
            puts("File sent");
        }
    } else if (!strcmp(tcpUdp, "UDP")) {
        serverConfig.protocol = "udp";
        SocketFileSender client(&clientConfig);
        if (client.SendFile(&serverConfig, path) == 1) {
            puts("File sent");
        }
    }
}

void UsagePrompt()
{
    puts("lab6 -server [TCP][UDP] \n lab4 -client [TCP][UDP] [path-to-file]");
}