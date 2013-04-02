#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;
Heap* heap_create();
void heap_destroy(Heap*);
int heap_extract_min(Heap*);
void heap_insert(Heap*, int);
int heap_peek(Heap*);
size_t heap_size(Heap*);

#endif
