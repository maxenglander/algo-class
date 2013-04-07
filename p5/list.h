#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "iterator.h"

typedef struct List List;

void list_add(List*, void* value);
List* list_create();
void list_destroy(List*);
bool list_empty(List*);
Iterator* list_iterator(List*);
size_t list_size(List*);

#endif
