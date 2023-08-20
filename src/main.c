#include <stdio.h>
#include <server.h>
#include <request.h>
#include <http_types.h>
#include <response.h>

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
    
    struct response_t* response = create_response();
    set_response_data(response, "<h1>http-server</h1><p>This http server has been created in C, click <a href=\"https://github.com/majorek31/http-server\">here</a> to see it's source code</p>", OK);
    send_response(fd, response);
    free_response(response);
    
    stop_server();
    return 0;
}