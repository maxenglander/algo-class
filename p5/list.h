#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "iterator.h"

typedef struct List List;

List* list_create();
void list_destroy(List*);
bool list_empty(List*);
void* list_head(List*);
Iterator* list_iterator(List*);
void* list_pop(List*);
void list_push(List*, void* value);
size_t list_size(List*);
void* list_tail(List*);

#endif
