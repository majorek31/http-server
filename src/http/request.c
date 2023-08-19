#include <request.h>
#include <http_headers.h>
#include <stdio.h>
#include <string.h>
int resolve_method(char* method) {
    if (!strcmp(method, "GET")) {
        return GET;
    } else if (!strcmp(method, "POST")) {
        return POST;
    } else {
        printf("Invalid request type: %s\n", method);
        return INVALID_REQUEST;
    }
}
void parse_headers(char* rawRequest, struct request_t* req) {
    char data[0x1000] = { 0 };
    strcpy(data, rawRequest);
    const char* delim = "\r\n";
    char* header = strtok(data, delim);
    header = strtok(NULL, delim);
    req->headers = create_header_list();
    while (header != NULL)
    {
        char* colon = strchr(header, ':');
        if (colon == NULL) {
            printf("Invalid header: %s\n", header);
            continue;
        }
        *colon = '\0'; // set null terminator at colon separator
        append_header(req->headers, header, colon + 2);
        header = strtok(NULL, delim);
    }
    
}
struct request_t parse_request(char* data, size_t len) {
    struct request_t request = { 0 };
    char method[0x10];
    int elements = sscanf(data, "%s /%s HTTP", method, request.requestedFile);
    request.method = resolve_method(method);
    if (elements != 2) {
        request.method = INVALID_REQUEST;
        return request;
    }
    parse_headers(data, &request);
    return request;
}