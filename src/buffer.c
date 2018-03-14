#include "buffer.h"

buffer *budder_create()
{
    buffer *new_buffer = (buffer *)malloc(sizeof(buffer));
    new_buffer->first = NULL;
    new_buffer->last = NULL;
    return new_buffer;
}

void buffer_add_message(buffer *buffer, void *data, size_t data_size)
{
    simple_node *node = node_create();
    node->data = malloc(data_size);
    node->data = data;
    (buffer->last)->next = node;
    buffer->last = node;
}

void *buffer_retrieve_message(buffer *buffer)
{
    simple_node *temp = buffer->first;
    buffer->first = temp->next == NULL ? NULL : temp->next;
    return temp;
}

void buffer_destroy(buffer **buffer)
{
    (*buffer)->last = NULL;
    while ((*buffer)->first != NULL)
    {
        simple_node *temp = (*buffer)->first;
        (*buffer)->first = temp->next;
        free(temp);
    }
    free(*buffer);
}