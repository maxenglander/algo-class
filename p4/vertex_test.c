#include <assert.h>
#include <stdio.h>
#include "vertex.h"

void test_vertex_add_head() {
  VERTEX* vertex = vertex_create();
  int i;
  int end = 20;

  for(i = 0; i < end; i++) {
    vertex_add_head(vertex, i);
  }

  for(i = 0; i < end; i++) {
    assert(vertex_has_head(vertex, i));
  }

  assert(end == vertex_num_heads(vertex));

  vertex_destroy(vertex);
}

void test_vertex_create() {
  VERTEX* vertex = vertex_create();
  assert(0 == vertex_num_heads(vertex));
  assert(NULL != vertex_heads(vertex));
  vertex_destroy(vertex);
}

void test_vertex_destroy() {
  VERTEX* vertex = vertex_create();
  vertex_destroy(vertex);
}

int main() {
  test_vertex_create();
  test_vertex_destroy();
  test_vertex_add_head();
  return 0;
}
