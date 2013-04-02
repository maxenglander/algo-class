#include <math.h>
#include <stdlib.h>
#include "heap.h"

#define HEAP_INITIAL_CAPACITY 10
#define HEAP_LOAD_FACTOR 0.75

struct Heap {
  int* array;
  size_t capacity;
  size_t size;
};

size_t heap_capacity(Heap* heap) {
  return heap->capacity;
}

Heap* heap_create() {
  Heap* heap = (Heap*)malloc(sizeof(Heap));
  heap->size = 0;
  heap->capacity = HEAP_INITIAL_CAPACITY;
  heap->array = (int*)calloc(HEAP_INITIAL_CAPACITY, sizeof(int));
  return heap;
}

void heap_destroy(Heap* heap) {
  free(heap->array);
  free(heap);
}

int heap_get(Heap* heap, unsigned int index) {
  return heap->array[index];
}

int heap_last_index(Heap* heap) {
  return heap->size - 1;
}

unsigned int heap_left_child_index(unsigned int index) {
  return index * 2 + 1;
}

int heap_left_child(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_left_child_index(index));
}

int heap_min(Heap* heap) {
  return heap_get(heap, 0);
}

unsigned int heap_parent_index(unsigned int index) {
  return (index % 2 == 1) ? (index - 1) / 2 : (index - 2) / 2;
}

int heap_parent(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_parent_index(index));
}

unsigned int heap_right_child_index(unsigned int index) {
  return index * 2 + 2; 
}

int heap_right_child(Heap* heap, unsigned int index) {
  return heap_get(heap, heap_right_child_index(index));
}

void heap_resize(Heap* heap) {
  heap->capacity = heap->capacity * 2;
  heap->array = (int*)realloc(heap->array, heap->capacity * sizeof(int));
}

void heap_set(Heap* heap, unsigned int index, int value) {
  heap->array[index] = value;
}

size_t heap_size(Heap* heap) {
  return heap->size;
}

int heap_last(Heap* heap) {
  return heap_get(heap, heap_last_index(heap));
}

void heap_swap(Heap* heap, int index0, int index1) {
  int temp = heap_get(heap, index0);
  heap_set(heap, index0, heap_get(heap, index1));
  heap_set(heap, index1, temp);
}

void heap_bubble_down(Heap* heap, int index) {
  if(heap_left_child_index(index) <= heap_last_index(heap)) {
    if(heap_get(heap, index) > heap_left_child(heap, index)) {
      heap_swap(heap, index, heap_left_child_index(index));
      heap_bubble_down(heap, heap_left_child_index(index));
      return;
    } 
  }
  
  if(heap_right_child_index(index) <= heap_last_index(heap)) {
    if(heap_get(heap, index) > heap_right_child(heap, index)) {
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

  if(heap_get(heap, index) < heap_parent(heap, index)) {
    heap_swap(heap, index, heap_parent_index(index));
    heap_bubble_up(heap, heap_parent_index(index));
  }
}

int heap_extract_min(Heap* heap) {
  int min = heap_min(heap);

  if(heap_size(heap) > 0) {
    heap_set(heap, 0, heap_last(heap));
    heap_bubble_down(heap, 0);
  }

  heap->size--;

  return min;
}

void heap_insert(Heap* heap, int value) {
  if(heap_capacity(heap) * HEAP_LOAD_FACTOR <= heap_size(heap)) {
    heap_resize(heap);
  }

  unsigned int next_index = heap_last_index(heap) + 1;

  heap_set(heap, next_index, value);

  heap->size++;
  
  heap_bubble_up(heap, next_index);
}
