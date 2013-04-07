#include <assert.h>
#include "list.h"

int main() {
  int a = 1;
  int b = 2;
  int c = 3;

  List* list = list_create();

  assert(0 == list_size(list));

  list_add(list, &a);
  list_add(list, &b);
  list_add(list, &c);

  assert(3 == list_size(list));

  list_destroy(list);
  return 0;
}
