#include <assert.h>
#include <stdio.h>
#include "graph.h"
#include "graph_search.h"
#include "vertex.h"

int main() {
  Graph* graph = graph_create();
  graph_add_edge(graph, 0, 1, 1);
  graph_add_edge(graph, 0, 2, 4);
  graph_add_edge(graph, 1, 2, 2);
  graph_add_edge(graph, 1, 3, 6);
  graph_add_edge(graph, 2, 3, 3);

  Vertex* source = graph_vertex(graph, 0);

  GraphSearch* graph_search = graph_search_create(graph);
  graph_search_find_shortest_paths(graph_search, source);
  assert(0 == graph_search_shortest_path(graph_search, graph_vertex(graph, 0)));
  assert(1 == graph_search_shortest_path(graph_search, graph_vertex(graph, 1)));
  assert(3 == graph_search_shortest_path(graph_search, graph_vertex(graph, 2)));
  assert(6 == graph_search_shortest_path(graph_search, graph_vertex(graph, 3)));

  graph_search_destroy(graph_search);
  graph_destroy(graph);

  return 0;
}
