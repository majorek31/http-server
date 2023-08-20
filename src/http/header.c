#include <http_headers.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

struct header_node* create_header_list() {
    struct header_node* head = malloc(sizeof(struct header_node));
    assert(head);
    memset(head, 0, sizeof(struct header_node));
    strcpy(head->name, "HEAD");
    return head;
}
void append_header(struct header_node* headers, char* name, char* value) {
    struct header_node* cur = headers;
    while (cur != NULL)
    {
        if (cur->next == NULL) {
            cur->next = malloc(sizeof(struct header_node));
            assert(cur->next);
            cur = cur->next;
            memset(cur, 0, sizeof(struct header_node));
            strcpy(cur->name, name);
            strcpy(cur->value, value);
            return;
        }
        cur = cur->next;
    }
}
void free_headers(struct header_node* headers) {
    struct header_node* cur = headers;
    while (cur != NULL)
    {
        struct header_node* next = cur->next;
        free(cur);
        cur = next;
    }
}
char* get_header(struct header_node* headers, char* name) {
    struct header_node* cur = headers;
    while (cur != NULL)
    {
        if (!strcmp(cur->name, name))
            return cur->value;
        cur = cur->next;
    }
}
int get_headers_size(struct header_node* headers) {
    int size = 0;
    struct header_node* cur = headers->next;
    while (cur != NULL)
    {
        if (cur->name != NULL && cur->value != NULL) {
            size += strlen(cur->name);
            size += strlen(cur->value);
            size += 2;
        }
        cur = cur->next;
    }
    return size;
}