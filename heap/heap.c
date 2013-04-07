#include <math.h>
#include <stdlib.h>
#include "heap.h"

#define HEAP_INITIAL_CAPACITY 10
#define HEAP_LOAD_FACTOR 0.75

struct Heap {
  void** array;
  size_t capacity;
  int (*comparator)(void*, void*);
  size_t size;
};

size_t heap_capacity(Heap* heap) {
  return heap->capacity;
}

Heap* heap_create(int (*comparator)(void*, void*)) {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->array = (void**)calloc(HEAP_INITIAL_CAPACITY, sizeof(void*));
  heap->capacity = HEAP_INITIAL_CAPACITY;
  heap->comparator = comparator;
  heap->size = 0;
  return heap;
}

void heap_destroy(Heap* heap) {
  free(heap->array);
  free(heap);
}

void* heap_get(Heap* heap, unsigned int index) {
  return heap->array[index];
}

int heap_last_index(Heap* heap) {
  return heap->size - 1;
}

unsigned int heap_left_child_index(unsigned int index) {
  return index * 2 + 1;
}

void* heap_left_child(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_left_child_index(index));
}

void* heap_min(Heap* heap) {
  return heap_get(heap, 0);
}

unsigned int heap_parent_index(unsigned int index) {
  return (index % 2 == 1) ? (index - 1) / 2 : (index - 2) / 2;
}

void* heap_parent(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_parent_index(index));
}

unsigned int heap_right_child_index(unsigned int index) {
  return index * 2 + 2; 
}

void* heap_right_child(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_right_child_index(index));
}

void heap_resize(Heap* heap) {
  heap->capacity = heap->capacity * 2;
  heap->array = (void**)realloc(heap->array, heap->capacity * sizeof(void*));
}

void heap_set(Heap* heap, unsigned int index, void* value) {
  heap->array[index] = value;
}

size_t heap_size(Heap* heap) {
  return heap->size;
}

void* heap_last(Heap* heap) {
  return heap_get(heap, heap_last_index(heap));
}

void heap_swap(Heap* heap, int index0, int index1) {
  void* temp = heap_get(heap, index0);
  heap_set(heap, index0, heap_get(heap, index1));
  heap_set(heap, index1, temp);
}

void heap_bubble_down(Heap* heap, int index) {
  if(heap_left_child_index(index) <= heap_last_index(heap)) {
    int left_compare = heap->comparator(heap_get(heap, index), heap_left_child(heap, index));
    if(1 == left_compare) {
      heap_swap(heap, index, heap_left_child_index(index));
      heap_bubble_down(heap, heap_left_child_index(index));
      return;
    } 
  }
  
  if(heap_right_child_index(index) <= heap_last_index(heap)) {
    int right_compare = heap->comparator(heap_get(heap, index), heap_right_child(heap, index));
    if(1 == right_compare) {
      heap_swap(heap, index, heap_right_child_index(index));
      heap_bubble_down(heap, heap_right_child_index(index));
      return;
    }
  }

  return;
}

void heap_bubble_up(Heap* heap, int index) {
  if(index == 0) {
    return;
  }

  int compare = heap->comparator(heap_get(heap, index), heap_parent(heap, index));
  if(compare <= 0) {
    heap_swap(heap, index, heap_parent_index(index));
    heap_bubble_up(heap, heap_parent_index(index));
  }
}

void* heap_extract_min(Heap* heap) {
  void* min = heap_min(heap);

  if(heap_size(heap) > 0) {
    heap_set(heap, 0, heap_last(heap));
    heap_bubble_down(heap, 0);
  }

  heap->size--;

  return min;
}

void heap_insert(Heap* heap, void* value) {
  if(heap_capacity(heap) * HEAP_LOAD_FACTOR <= heap_size(heap)) {
    heap_resize(heap);
  }

  unsigned int next_index = heap_last_index(heap) + 1;

  heap_set(heap, next_index, value);

  heap->size++;
  
  heap_bubble_up(heap, next_index);
}
