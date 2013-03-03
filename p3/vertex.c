#include <stdlib.h>
#include <string.h>
#include "vertex.h"

VERTEX* vertex_copy(VERTEX* vertex) {
  return vertex = vertex_create(vertex->label);
}

VERTEX* vertex_create(int label) {
  VERTEX* vertex = (VERTEX*)malloc(sizeof(VERTEX));
  vertex->label = label;
  return vertex;
}

void vertex_destroy(VERTEX* vertex) {
  free(vertex);
}

VERTEX* vertex_tokenize(char* line, char* delim, char** context) {
  char* vertex_label_string = strtok_r(line, delim, context);

  if(vertex_label_string == NULL) {
    return NULL;
  }

  char* endptr = NULL;
  int vertex_label = (int)strtol(vertex_label_string, &endptr, 10);

  return vertex_create(vertex_label);
}
