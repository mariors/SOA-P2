#include "simple_node.h"

simple_node *node_create()
{
    simple_node *new_node = (simple_node *)malloc(sizeof(simple_node));
    new_node->data = NULL;
    new_node->next = NULL;
    return new_node;
}

void node_destroy(simple_node **node)
{
    if ((*node)->data != NULL)
    {
        free((*node)->data);
    }
    free(*node);
}
