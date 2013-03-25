#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

#include <stdbool.h>
#include "graph.h"

typedef struct {
  bool* explored_vertices;
  unsigned int* finish_times;
  size_t num_finished;
  size_t num_sccs;
  size_t* scc_sizes;
} GRAPH_SEARCH;

GRAPH_SEARCH* graph_search_create(GRAPH*);
void graph_search_destroy(GRAPH_SEARCH*);
void graph_search_finish_times(GRAPH*, GRAPH_SEARCH*);
void graph_search_sccs(GRAPH*, GRAPH_SEARCH*, int* search_order);

#endif
