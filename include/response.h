#pragma once
#include <stdint.h>

struct response_t
{
    int status;
    struct header_node* headers;
    uint64_t dataLen;
    char* data;
};

struct response_t* create_response();
void free_response(struct response_t* response);
int send_response(int fd, struct response_t* response);
void set_response_data(struct response_t* response, char* data, int status);