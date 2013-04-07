#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include "graph.h"
#include "vertex.h"

typedef struct GraphSearch GraphSearch;

GraphSearch* graph_search_create(Graph*);
void graph_search_destroy(GraphSearch*);
void graph_search_find_shortest_paths(GraphSearch*, Vertex* source);
size_t graph_search_num_paths(GraphSearch*);
unsigned int graph_search_shortest_path(GraphSearch*, Vertex* target);

#endif
