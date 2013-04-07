#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;
Heap* heap_create(int (*comparator)(void*, void*));
void heap_destroy(Heap*);
void* heap_extract_min(Heap*);
void heap_insert(Heap*, void*);
void* heap_peek(Heap*);
size_t heap_size(Heap*);

#endif
