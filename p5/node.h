#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node Node;

Node* node_create(void* value);
void node_destroy(Node* node);
bool node_has_next(Node*);
Node* node_next(Node*);
void node_set_next(Node*, Node*);
void* node_value(Node*);

#endif
