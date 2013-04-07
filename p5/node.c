#include "node.h"

struct Node {
  Node* next;
  Node* previous;
  void* value;
};

Node* node_create(void* value) {
  Node* node = (Node*)malloc(sizeof(Node*));
  node->next = NULL;
  node->previous = NULL;
  node->value = value;
  return node;
}

void node_destroy(Node* node) {
  free(node);
}

Node* node_next(Node* node) {
  return node->next;
}

Node* node_previous(Node* node) {
  return node->previous;
}

bool node_has_next(Node* node) {
  return node_next(node) != NULL;
}

bool node_has_previous(Node* node) {
  return node_previous(node) != NULL;
}

void node_set_next(Node* node, Node* next) {
  node->next = next;
}

void node_set_previous(Node* node, Node* previous) {
  node->previous = previous;
}

void* node_value(Node* node) {
  return node->value;
}
