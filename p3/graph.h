#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "vertex.h"

#define DEFAULT_EDGE_CAPACITY 1000 
#define DEFAULT_LOAD_FACTOR 1.1
#define DEFAULT_VERTEX_CAPACITY 100

typedef struct {
  size_t num_edges;
  size_t num_vertices;

  size_t edge_capacity;
  size_t vertex_capacity;

  double load_factor;

  VERTEX** vertices;
  EDGE** edges;
} GRAPH;

GRAPH* graph_create(size_t vertex_capacity, size_t edge_capacity, double load_factor);
void graph_destroy(GRAPH* graph);
int graph_find_min_cut(GRAPH* graph);
GRAPH* graph_load_from_file(const char* file_path);

#endif
