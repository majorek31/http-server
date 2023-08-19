#include <server.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <unistd.h>
int serverSocket = 0;
int start_server(uint16_t port) {
    int status = 0;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("socket() failed\n");
        return 1;
    }
    struct sockaddr_in addr = { 0 };
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    status = bind(serverSocket, (const struct sockaddr*)&addr, sizeof(addr));
    if (status == -1) {
        printf("bind() failed\n");
        return 1;
    }
    status = listen(serverSocket, 5);
    if (status == -1) {
        printf("listen() failed\n");
        return 1;
    }
    return 0;
}
int accept_connection() {
    return accept(serverSocket, 0, 0);
}
void stop_server() {
    close(serverSocket);
    close(serverSocket);
    printf("Server stopped\n");
}