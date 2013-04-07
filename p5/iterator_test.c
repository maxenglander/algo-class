#include <assert.h>
#include <stdbool.h>
#include "iterator.h"
#include "list.h"

int main() {
  int a = 5;
  int b = 10;
  int c = 20;

  List* list = list_create();

  Iterator* iterator = list_iterator(list);

  assert(false == iterator_has_next(iterator));

  iterator_destroy(iterator);

  list_push(list, &a);
  list_push(list, &b);
  list_push(list, &c);

  iterator = list_iterator(list);

  assert(true == iterator_has_next(iterator));
  assert(&a == iterator_next(iterator));
  assert(&b == iterator_next(iterator));
  assert(&c == iterator_next(iterator));
  assert(false == iterator_has_next(iterator));

  iterator_destroy(iterator);
  
  return 0;
}
