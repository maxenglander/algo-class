#include <assert.h>
#include "vertex.h"

int main() {
  Vertex* vertex = vertex_create(8);
  vertex_destroy(vertex);
  return 0;
}
