#include <stdlib.h>
#include "graph_search.h"

void graph_search_dfs(GRAPH*, GRAPH_SEARCH*, unsigned int tail);

bool graph_search_explored(GRAPH_SEARCH*, unsigned int);

GRAPH_SEARCH* graph_search_create(GRAPH* graph) {
  GRAPH_SEARCH* graph_search = (GRAPH_SEARCH*)malloc(sizeof(GRAPH_SEARCH));
  graph_search->explored_vertices = (bool*)calloc(graph_num_vertices(graph), sizeof(bool));
  graph_search->finish_times = (int*)calloc(graph_num_vertices(graph), sizeof(unsigned int));
  graph_search->num_finished = 0;
  return graph_search;
}

void graph_search_destroy(GRAPH_SEARCH* graph_search) {
  free(graph_search->explored_vertices);
  free(graph_search->finish_times);
  free(graph_search);
}

void graph_search_dfs(GRAPH* graph, GRAPH_SEARCH* graph_search, unsigned int tail) {
  graph_search->explored_vertices[tail] = true;
  VERTEX* vertex = graph_vertex(graph, tail);

  unsigned int head_index;
  for(head_index = 0; head_index < vertex_num_heads(vertex); head_index++) {
    unsigned int head = vertex_head(vertex, head_index);
    if(!graph_search_explored(graph_search, head)) {
      graph_search_dfs(graph, graph_search, head);
    }
  }

  graph_search->num_finished++;
  graph_search->finish_times[tail] = graph_search->num_finished - 1;
}

bool graph_search_explored(GRAPH_SEARCH* graph_search, unsigned int vertex) {
  return graph_search->explored_vertices[vertex];
}

void graph_search_finish_times(GRAPH* graph, GRAPH_SEARCH* graph_search) {
  int tail;
  for(tail = graph_num_vertices(graph) - 1; tail >= 0; tail--) {
    if(!graph_search_explored(graph_search, tail)) {
      graph_search_dfs(graph, graph_search, tail);
    }
  }
}
