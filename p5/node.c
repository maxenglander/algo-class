#include "node.h"

struct Node {
  Node* next;
  void* value;
};

Node* node_create(void* value) {
  Node* node = (Node*)malloc(sizeof(Node*));
  node->next = NULL;
  node->value = value;
  return node;
}

void node_destroy(Node* node) {
  free(node);
}

Node* node_next(Node* node) {
  return node->next;
}

bool node_has_next(Node* node) {
  return node_next(node) != NULL;
}

void node_set_next(Node* node, Node* next) {
  node->next = next;
}

void* node_value(Node* node) {
  return node->value;
}
