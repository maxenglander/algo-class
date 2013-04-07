#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "vertex.h"

typedef struct Graph Graph;

void graph_add_edge(Graph*, unsigned int tail, unsigned int head, unsigned int length);
Graph* graph_create();
void graph_destroy(Graph*);
Graph* graph_load_from_file(const char* file_path);
size_t graph_num_vertices(Graph*);
Vertex* graph_vertex(Graph*, unsigned int label);

#endif
