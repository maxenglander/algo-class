#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void test_heap_create_destroy() {
  Heap* heap = heap_create();
  assert(0 == heap_size(heap));
}

void test_heap_insert_extract_min() {
  Heap* heap = heap_create();

  heap_insert(heap, -2);
  heap_insert(heap, -20);
  heap_insert(heap, 5);
  heap_insert(heap, 2);
  heap_insert(heap, -5);

  assert(-20 == heap_extract_min(heap));
  assert(-5 == heap_extract_min(heap));
  assert(-2 == heap_extract_min(heap));
  assert(2 == heap_extract_min(heap));
  assert(5 == heap_extract_min(heap));

  heap_destroy(heap);
}

int main() {
  test_heap_create_destroy();
  test_heap_insert_extract_min();
  return 0;
}
