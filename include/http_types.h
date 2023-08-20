#pragma once

enum http_method {
    INVALID_REQUEST = -1,
    GET = 0,
    POST,
};

enum http_status {
    OK = 200,
    NOT_FOUND = 404,
};