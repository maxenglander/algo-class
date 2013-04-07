#include "list.h"
#include "node.h"

struct List {
  Node* head;
  size_t size;
  Node* tail;
};

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

void* list_head(List* list) {
  return list_empty(list) ? NULL : node_value(list->head);
}

Iterator* list_iterator(List* list) {
  return iterator_create(list->head);
}

void* list_pop(List* list) {
  void* tail_value = list_tail(list);

  Node* previous = node_previous(list->tail);
  free(list->tail);
  if(previous == NULL) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->tail = previous;
  }

  list->size--;
  return tail_value;
}

void list_push(List* list, void* value) {
  Node* node = node_create(value);

  if(list->head == NULL) {
    list->head = node;
  } else {
    node_set_next(list->tail, node);
    node_set_previous(node, list->tail);
  }

  list->tail = node;
  list->size++;
}

size_t list_size(List* list) {
  return list->size;
}

void* list_tail(List* list) {
  return list_empty(list) ? NULL : node_value(list->tail);
}
