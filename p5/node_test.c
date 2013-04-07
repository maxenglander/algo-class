#include <assert.h>
#include "node.h"

int main() {
  int a = 5;
  int b = 10;

  Node* node_a = node_create(&a);
  Node* node_b = node_create(&b);
  
  assert(&a == node_value(node_a));
  assert(&b == node_value(node_b));

  assert(NULL == node_next(node_a));
  assert(NULL == node_next(node_b));

  node_set_next(node_a, node_b);

  assert(node_b == node_next(node_a));
  assert(NULL == node_next(node_b));

  node_destroy(node_a);
  node_destroy(node_b);

  return 0;
}
