#pragma once
#include <stdint.h>

struct header_node
{
    char name[256];
    char value[256];
    struct header_node* next;
};

struct header_node* create_header_list();
void append_header(struct  header_node* headers, char* name, char* value);
void free_headers(struct  header_node* headers);
char* get_header(struct header_node* headers, char* name);