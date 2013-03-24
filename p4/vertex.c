#include <stdlib.h>
#include "vertex.h"

int vertex_head_capacity(VERTEX* vertex);
void vertex_resize(VERTEX* vertex);

void vertex_add_head(VERTEX* vertex, unsigned int head) {
  if(vertex_has_head(vertex, head)) {
    return;
  }

  vertex_resize(vertex);
  vertex->heads[vertex_num_heads(vertex) - 1] = head;
}

VERTEX* vertex_create() {
  VERTEX* vertex = (VERTEX*)malloc(sizeof(VERTEX));
  vertex->heads = (unsigned int*)calloc(0, sizeof(unsigned int));
  vertex->num_heads = 0;
  return vertex;
}

void vertex_destroy(VERTEX* vertex) {
  free(vertex->heads);
  free(vertex);
}

unsigned int vertex_head(VERTEX* vertex, unsigned int index) {
  return vertex->heads[index];
}

unsigned int* vertex_heads(VERTEX* vertex) {
  return vertex->heads;
}

size_t vertex_num_heads(VERTEX* vertex) {
  return vertex->num_heads;
}

bool vertex_has_head(VERTEX* vertex, unsigned int head) {
  int i;
  size_t num_heads = vertex_num_heads(vertex);
  for(i = 0; i < num_heads; i++) {
    if(vertex_head(vertex, i) == head) {
      return true;
    }
  }
  return false;
}

void vertex_resize(VERTEX* vertex) {
  size_t new_num_heads = vertex_num_heads(vertex) + 1;
  vertex->heads = (unsigned int*)realloc(vertex->heads, sizeof(unsigned int) * new_num_heads);
  vertex->num_heads = new_num_heads;
}
