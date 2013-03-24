#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <stdbool.h>
#include "graph.h"

typedef struct {
  bool* explored_vertices;
  int* finish_times;
  int num_finished;
} GRAPH_SEARCH;

GRAPH_SEARCH* graph_search_create(GRAPH*);
void graph_search_destroy(GRAPH_SEARCH*);
void graph_search_finish_times(GRAPH*, GRAPH_SEARCH*);

#endif
