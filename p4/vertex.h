#ifndef VERTEX_H
#define VERTEX_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t num_heads;
  unsigned int* heads;
} VERTEX;

void vertex_add_head(VERTEX*, unsigned int);
unsigned int vertex_head(VERTEX*, unsigned int);
unsigned int* vertex_heads(VERTEX*);
size_t vertex_num_heads(VERTEX*);
bool vertex_has_head(VERTEX*, unsigned int);
VERTEX* vertex_create();
void vertex_destroy(VERTEX*);

#endif
