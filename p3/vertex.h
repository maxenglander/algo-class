#ifndef VERTEX_H
#define VERTEX_H

typedef struct {
  int label;
} VERTEX;
VERTEX* vertex_copy(VERTEX* vertex);
VERTEX* vertex_create(int label);
void vertex_destroy(VERTEX* vertex);
VERTEX* vertex_tokenize(char* line, char* delim, char** context);

#endif
