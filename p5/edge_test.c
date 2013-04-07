#include <assert.h>
#include "edge.h"
#include "vertex.h"

int main() {
  Vertex* vertex = vertex_create(8);
  Edge* edge = edge_create(vertex, 10);

  assert(vertex == edge_vertex(edge));
  assert(10 == edge_length(edge));

  edge_destroy(edge);
  vertex_destroy(vertex);

  return 0;
}
