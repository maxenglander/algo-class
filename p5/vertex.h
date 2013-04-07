#ifndef VERTEX_H
#define VERTEX_H

#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

typedef struct Vertex Vertex;

void vertex_add_edge(Vertex* vertex, Vertex* head, unsigned int length);
Vertex* vertex_create(unsigned int label);
void vertex_destroy(Vertex*);
List* vertex_edges(Vertex*);
bool vertex_has_edges(Vertex*);
unsigned int vertex_label(Vertex* vertex);

#endif
