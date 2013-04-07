#include "edge.h"
#include "vertex.h"

struct Vertex {
  unsigned int label;
  List* edges;
};

void vertex_add_edge(Vertex* vertex, Vertex* head, unsigned int length) {
  if(vertex->edges == NULL) {
    vertex->edges = list_create();
  }

  Edge* edge = edge_create(head, length);
  list_add(vertex->edges, edge);
}

Vertex* vertex_create(unsigned int label) {
  Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
  vertex->label = label;
  vertex->edges = NULL;
}

void vertex_destroy(Vertex* vertex) {
  free(vertex);
}

List* vertex_edges(Vertex* vertex) {
  return vertex->edges;
}

bool vertex_has_edges(Vertex* vertex) {
  return vertex_edges(vertex) != NULL && !list_empty(vertex->edges);
}
