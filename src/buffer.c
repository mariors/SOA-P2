#include "buffer.h"

buffer *budder_create()
{
    buffer* new_buffer = (buffer*) malloc(sizeof(buffer));
    new_buffer->first = NULL;
    new_buffer->last = NULL;
    return new_buffer;
}

void buffer_add_message(const buffer * buffer, void* data, size_t data_size)
{
}

void *buffer_retrieve_message(const buffer * buffer)
{
}

void buffer_destroy(buffer ** buffer)
{
    free(*buffer);
}