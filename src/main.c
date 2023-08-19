#include <stdio.h>
#include <server.h>

int main(int argc, char** argv) {
    if (start_server(6969) != 0) {
        printf("Failed to start http server at localhost:6969\n");
        return -1;
    }
    printf("Started http server at http://localhost:6969\n");
    
    stop_server();
    return 0;
}