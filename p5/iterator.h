#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

typedef struct Iterator Iterator;

Iterator* iterator_create(Node*);
bool iterator_has_next(Iterator*);
void* iterator_next(Iterator*);
void iterator_destroy(Iterator*);

#endif
