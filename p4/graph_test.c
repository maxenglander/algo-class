#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void test_graph_add_edge() {
  GRAPH* graph = graph_create();
  graph_add_edge(graph, 0, 0);
  assert(1 == graph_num_vertices(graph));
  graph_add_edge(graph, 0, 1);
  assert(2 == graph_num_vertices(graph));
  graph_add_edge(graph, 0, 99);
  assert(100 == graph_num_vertices(graph));
  graph_add_edge(graph, 0, 99);
  graph_add_edge(graph, 1, 99);
  graph_add_edge(graph, 2, 99);
  assert(100 == graph_num_vertices(graph));
  graph_destroy(graph);
}

void test_graph_create() {
  GRAPH* graph = graph_create();
  assert(0 == graph_num_vertices(graph));
  assert(NULL != graph_vertices(graph));
}

void test_graph_destroy() {
  GRAPH* graph = graph_create();
  graph_destroy(graph);
}

void test_graph_load_from_file() {
  GRAPH* graph = graph_load_from_file("./graph_test.txt");
  assert(51 == graph_num_vertices(graph));
  assert(3 == vertex_num_heads(graph_vertex(graph, 0)));
  graph_destroy(graph);
}

void test_graph_reverse() {
  GRAPH* graph = graph_create();
  graph_add_edge(graph, 0, 1);
  graph_add_edge(graph, 0, 2);
  graph_add_edge(graph, 1, 2);

  GRAPH* reverse = graph_reverse(graph);
  assert(0 == vertex_num_heads(graph_vertex(reverse, 0)));
  assert(1 == vertex_num_heads(graph_vertex(reverse, 1)));
  assert(2 == vertex_num_heads(graph_vertex(reverse, 2)));
  assert(0 == vertex_head(graph_vertex(reverse, 1), 0));
  graph_destroy(graph);
  graph_destroy(reverse);
}

int main() {
  test_graph_create();
  test_graph_destroy();
  test_graph_add_edge();
  test_graph_load_from_file();
  test_graph_reverse();
  return 0;
}
