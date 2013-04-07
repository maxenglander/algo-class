#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

typedef struct Edge Edge;

Edge* edge_create(Vertex*, unsigned int);
void edge_destroy(Edge*);
unsigned int edge_length(Edge*);
Vertex* edge_vertex(Edge*);

#endif
