#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include "vertex.h"

typedef struct {
  size_t num_vertices;
  VERTEX** vertices;
} GRAPH;

void graph_add_edge(GRAPH*, unsigned int tail, unsigned int head);
unsigned int* graph_finish_times(GRAPH*);
size_t graph_num_vertices(GRAPH*);
GRAPH* graph_create();
void graph_destroy(GRAPH *);
GRAPH* graph_load_from_file(const char*);
GRAPH* graph_reverse(GRAPH*);
VERTEX* graph_vertex(GRAPH*, unsigned int tail);
VERTEX** graph_vertices(GRAPH*);

#endif
