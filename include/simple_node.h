#ifndef SIMPLE_NODE_H_
#define SIMPLE_NODE_H_

#include <stdlib.h>

typedef struct simple_node
{
    void *data;
    struct simple_node *next;
} simple_node;

simple_node *node_create();

void node_destroy(simple_node **);

#endif