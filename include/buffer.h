#ifndef BUFFER_H_
#define BUFFER_H_

#include "node.h"

typedef struct buffer
{
    simple_node *first;
    simple_node *last;
} buffer;

buffer *budder_create();

void buffer_add_message(buffer *, void *, size_t);

void *buffer_retrieve_message(buffer *);

void buffer_destroy(buffer **);

#endif