#include "iterator.h"

struct Iterator {
  Node* current;
  Node* list_head;
};

Iterator* iterator_create(Node* list_head) {
  Iterator* iterator = (Iterator*)malloc(sizeof(Iterator));
  iterator->list_head = list_head;
}

void iterator_destroy(Iterator* iterator) {
  free(iterator);
}

bool iterator_has_next(Iterator* iterator) {
  if(iterator->list_head == NULL) {
    return false;
  }

  if(iterator->current == NULL) {
    return true;
  }

  return node_has_next(iterator->current);
}

void* iterator_next(Iterator* iterator) {
  if(iterator->current == NULL) {
    iterator->current = iterator->list_head;
  } else if(node_has_next(iterator->current)) {
    iterator->current = node_next(iterator->current);
  } else {
    iterator->current = NULL;
  }

  return node_value(iterator->current);
}
