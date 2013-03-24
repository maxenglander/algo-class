#include <assert.h>
#include <stdio.h>
#include "graph_search.h"

void test_graph_search_create() {
  GRAPH* graph = graph_create();
  graph_add_edge(graph, 0, 1);
  graph_add_edge(graph, 0, 2);
  graph_add_edge(graph, 1, 2);
  graph_add_edge(graph, 2, 1);

  GRAPH_SEARCH* graph_search = graph_search_create(graph);
  graph_destroy(graph);
}

void test_graph_search_destroy() {
  GRAPH* graph = graph_create();
  graph_add_edge(graph, 0, 1);
  graph_add_edge(graph, 0, 2);
  graph_add_edge(graph, 1, 2);
  graph_add_edge(graph, 2, 1);

  GRAPH_SEARCH* graph_search = graph_search_create(graph);
  graph_destroy(graph);
  graph_search_destroy(graph_search);
}

void test_graph_search_finish_times() {
  GRAPH* graph = graph_create();
  graph_add_edge(graph, 0, 6);
  graph_add_edge(graph, 6, 3);
  graph_add_edge(graph, 3, 0);
  graph_add_edge(graph, 6, 8);
  graph_add_edge(graph, 8, 5);
  graph_add_edge(graph, 5, 2);
  graph_add_edge(graph, 2, 8);
  graph_add_edge(graph, 5, 7);
  graph_add_edge(graph, 7, 1);
  graph_add_edge(graph, 1, 4);
  graph_add_edge(graph, 4, 7);

  GRAPH_SEARCH* graph_search = graph_search_create(graph);
  graph_search_finish_times(graph, graph_search);
  graph_destroy(graph);

  assert(6 == graph_search->finish_times[0]);
  assert(2 == graph_search->finish_times[1]);
  assert(0 == graph_search->finish_times[2]);
  assert(7 == graph_search->finish_times[3]);
  assert(1 == graph_search->finish_times[4]);
  assert(4 == graph_search->finish_times[5]);
  assert(8 == graph_search->finish_times[6]);
  assert(3 == graph_search->finish_times[7]);
  assert(5 == graph_search->finish_times[8]);

  graph_search_destroy(graph_search);
}

int main() {
  test_graph_search_create();
  test_graph_search_destroy();
  test_graph_search_finish_times();
  return 0;
}
