#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

typedef struct {
  VERTEX* left;
  VERTEX* right;
} EDGE;
EDGE* edge_copy(EDGE* edge);
EDGE* edge_create(VERTEX*, VERTEX*);
void edge_destroy(EDGE*);
void edge_print(EDGE*);

#endif
