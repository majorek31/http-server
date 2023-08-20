#include <stdio.h>
#include <server.h>
#include <request.h>
#include <http_types.h>

int main(int argc, char** argv) {
    if (start_server(6969) != 0) {
        printf("Failed to start http server at localhost:6969\n");
        return -1;
    }
    printf("Started http server at http://localhost:6969\n");
    int fd = accept_connection();
    char buf[0x1000] = { 0 }; 
    recv(fd, buf, 0x1000, 0);
    struct request_t req = parse_request(buf, 0x1000);
    printf("method: %d file: %s\n", req.method, req.requestedFile);
    printf("User agent: '%s'\n", get_header(req.headers, "User-Agent"));
    free_headers(req.headers);
    stop_server();
    return 0;
}