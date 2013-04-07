#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graph_search.h"
#include "vertex.h"

void usage(char* arg0) {
  printf("%s <file> <source_vertex>\n", arg0);
}

int main(int argc, char** argv) {
  if(argc != 3) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  char* file = argv[1];
  Graph* graph = graph_load_from_file(file);
  int source_vertex_label = atoi(argv[2]);
  Vertex* source = graph_vertex(graph, source_vertex_label);

  GraphSearch* graph_search = graph_search_create(graph);
  graph_search_find_shortest_paths(graph_search, source);

  unsigned int i;
  for(i = 0; i < graph_search_num_paths(graph_search); i++) {
    Vertex* target = graph_vertex(graph, i);
    if(target != NULL) {
      printf("%u -> %u : %u\n", source_vertex_label, vertex_label(target), graph_search_shortest_path(graph_search, target));
    }
  }

  graph_search_destroy(graph_search);
  graph_destroy(graph);

  return 0;
}
