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

  GRAPH_SEARCH* graph_search1 = graph_search_create(reverse);
  graph_search_finish_times(reverse, graph_search1);

  GRAPH_SEARCH* graph_search2 = graph_search_create(graph);
  graph_search_sccs(graph, graph_search2, graph_search1->finish_times);

  int i;
  for(i = 0; i < graph_search2->num_sccs; i++) {
    printf("%zu\n", graph_search2->scc_sizes[i]);
  }

  graph_search_destroy(graph_search1);
  graph_search_destroy(graph_search2);

  graph_destroy(reverse);
  graph_destroy(graph);

  return 0;
}

void usage(char** argv) {
  printf("%s <file>\n", argv[0]);
}
