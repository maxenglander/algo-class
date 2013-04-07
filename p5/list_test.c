#include <assert.h>
#include "list.h"

int main() {
  int a = 1;
  int b = 2;
  int c = 3;

  List* list = list_create();

  assert(0 == list_size(list));

  list_push(list, &a);
  list_push(list, &b);
  list_push(list, &c);

  assert(3 == list_size(list));

  assert(&c == (int*)list_pop(list));
  assert(2 == list_size(list));
  assert(&b == (int*)list_pop(list));
  assert(1 == list_size(list));
  assert(&a == (int*)list_pop(list));
  assert(true == list_empty(list));

  list_destroy(list);
  return 0;
}
