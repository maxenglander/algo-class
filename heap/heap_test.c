#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int comparator(void* a, void* b) {
  int va = *(int*)a;
  int vb = *(int*)b;
  if(va < vb) {
    return -1;
  } else if(va == vb) {
    return 0;
  } else if(va > vb) {
    return 1;
  }
}

void test_heap_create_destroy() {
  Heap* heap = heap_create(comparator);
  assert(0 == heap_size(heap));
}

void test_heap_insert_extract_min() {
  Heap* heap = heap_create(comparator);

  int neg_two = -2;
  int neg_five = -5;
  int neg_twenty = -20;
  int pos_two = 2;
  int pos_five = 5;

  heap_insert(heap, &neg_two);
  heap_insert(heap, &neg_twenty);
  heap_insert(heap, &pos_five);
  heap_insert(heap, &pos_two);
  heap_insert(heap, &neg_five);

  assert(&neg_twenty == heap_extract_min(heap));
  assert(&neg_five == heap_extract_min(heap));
  assert(&neg_two == heap_extract_min(heap));
  assert(&pos_two == heap_extract_min(heap));
  assert(&pos_five == heap_extract_min(heap));

  heap_destroy(heap);
}

int main() {
  test_heap_create_destroy();
  test_heap_insert_extract_min();
  return 0;
}
