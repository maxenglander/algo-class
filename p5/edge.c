#include "edge.h"

struct Edge {
  Vertex* vertex;
  unsigned int length;
};

Edge* edge_create(Vertex* vertex, unsigned int length) {
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->length = length;
  edge->vertex = vertex;
  return edge;
}

void edge_destroy(Edge* edge) {
  free(edge);
}

unsigned int edge_length(Edge* edge) {
  return edge->length;
}

Vertex* edge_vertex(Edge* edge) {
  return edge->vertex;
}
