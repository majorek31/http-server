#pragma once
#include <sys/socket.h>
#include <http_types.h>
#include <http_headers.h>

struct request_t
{
    enum http_method method;
    struct header_node* headers;
    char requestedFile[255];
};

struct request_t parse_request(char* data, size_t len);