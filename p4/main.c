#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graph_search.h"

void usage(char** argv);

int main(int argc, char** argv) {
  if(argc < 2) {
    usage(argv);
    exit(EXIT_FAILURE);
  }

  GRAPH* graph = graph_load_from_file(argv[1]);
  GRAPH* reverse = graph_reverse(graph);
  GRAPH_SEARCH* graph_search = graph_search_create(graph);

  graph_search_destroy(graph_search);
  graph_destroy(reverse);
  graph_destroy(graph);

  return 0;
}

void usage(char** argv) {
  printf("%s <file>\n", argv[0]);
}
