#pragma once
#include <sys/socket.h>
#include <stdint.h>

int start_server(uint16_t port);
int accept_connection();
void stop_server();