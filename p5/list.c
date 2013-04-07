#include "list.h"
#include "node.h"

struct List {
  Node* head;
  size_t size;
  Node* tail;
};

void list_add(List* list, void* value) {
  Node* node = node_create(value);

  if(list->head == NULL) {
    list->head = node;
  } else {
    node_set_next(list->tail, node);
  }

  list->tail = node;
  list->size++;
}

List* list_create() {
  List* list = (List*)malloc(sizeof(List));
  list->head = NULL;
  list->size = 0;
  list->tail = NULL;
  return list;
}

void list_destroy(List* list) {
  free(list);
}

bool list_empty(List* list) {
  return list_size(list) == 0;
}

Iterator* list_iterator(List* list) {
  return iterator_create(list->head);
}

size_t list_size(List* list) {
  return list->size;
}
