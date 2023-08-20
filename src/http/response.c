#include <response.h>
#include <sys/socket.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <http_types.h>
#include <http_headers.h>

struct response_t* create_response() {
    struct response_t* res = malloc(sizeof(struct response_t));
    assert(res);
    memset(res, 0, sizeof(struct response_t));
    res->headers = create_header_list();
    assert(res->headers);
    return res;
}
void free_response(struct response_t* response) {
    if (response == NULL)
        return;
    if(response->data != NULL)
        free(response->data);
    if(response->headers != NULL)
        free_headers(response->headers);
    free(response);
}
int create_response_header(char* rawBuffer, int status) {
    switch (status)
    {
        case OK: {
            sprintf(rawBuffer, "HTTP/1.1 200 OK\r\n");
        } break;
        case NOT_FOUND: {
            sprintf(rawBuffer, "HTTP/1.1 404 Not Found\r\n");
        } break;
        default: {
            printf("Invalid response code!\n");
        } break;
    }
    return 1;
}
int populate_response_with_headers(char* rawBuffer, struct response_t* response) {
    struct header_node* cur = response->headers->next;
    while (cur != NULL)
    {
        char buf[0x512] = { 0 };
        sprintf(buf, "%s: %s\r\n", cur->name, cur->value);
        strcat(rawBuffer, buf);
        cur = cur->next;
    }
    strcat(rawBuffer, "\r\n");
}
void set_response_data(struct response_t* response, char* data, int status) {
    int size = strlen(data);
    response->status = status;
    response->data = malloc(size);
    assert(response->data);
    strcat(response->data, "\r\n");
    strcpy(response->data, data);
    response->dataLen = size;
}
int send_response(int fd, struct response_t* response) {
    char len[16] = { 0 };
    sprintf(len, "%ld", response->dataLen);
    append_header(response->headers, "Content-Length", len);
    append_header(response->headers, "Server", "HTTP@majorek31");
    append_header(response->headers, "Content-Type", "text/html");
    append_header(response->headers, "Connection", "Closed");
    int size = get_headers_size(response->headers);
    size += response->dataLen;
    size += 32; // some additional buffer
    char* rawBuffer = malloc(size);
    memset(rawBuffer, 0, size);
    create_response_header(rawBuffer, response->status);
    populate_response_with_headers(rawBuffer, response);
    strcat(rawBuffer, response->data);
    printf("''%s''", rawBuffer);
    send(fd, rawBuffer, size, 0);
    free(rawBuffer);
}