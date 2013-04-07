#include <assert.h>
#include "graph.h"

void test_graph_create_and_destroy() {
  Graph* graph = graph_create();
  assert(0 == graph_num_vertices(graph));
  graph_destroy(graph);
}

void test_graph_vertex_and_add_edge() {
  Graph* graph = graph_create();

  graph_add_edge(graph, 0, 1000, 30);
  assert(2 == graph_num_vertices(graph));

  graph_add_edge(graph, 800, 1000, 120);
  assert(3 == graph_num_vertices(graph));

  graph_add_edge(graph, 1000, 0, 90);
  assert(3 == graph_num_vertices(graph));

  graph_add_edge(graph, 1000, 2000, 180);
  assert(4 == graph_num_vertices(graph));

  graph_destroy(graph);
}

void test_graph_load_from_file() {
  Graph* graph = graph_load_from_file("./graph_test.txt");
  graph_destroy(graph);
}

int main() {
  test_graph_create_and_destroy();
  test_graph_vertex_and_add_edge();
  test_graph_load_from_file();
  return 0;
}
