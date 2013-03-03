#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"

EDGE* edge_copy(EDGE* edge) {
  return edge_create(vertex_copy(edge->left), vertex_copy(edge->right));
}

EDGE* edge_create(VERTEX* left, VERTEX* right) {
  if (left == right) {
    return NULL;
  }
  EDGE* edge = (EDGE*)malloc(sizeof(EDGE));
  bool flip = right->label < left->label;
  edge->left = !flip ? left : right;
  edge->right = !flip ? right : left;
  return edge;
}

void edge_destroy(EDGE* edge) {
  free(edge);
}

void edge_print(EDGE* edge) {
  printf("Edge %i, %i\n", edge->left->label, edge->right->label);
}
