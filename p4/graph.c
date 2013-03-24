#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graph.h"

void graph_resize(GRAPH* graph, size_t num_vertices);

void graph_add_edge(GRAPH* graph, unsigned int tail, unsigned int head) {
  unsigned int max_of_head_and_tail = head > tail ? head : tail;
  size_t required_num_vertices = max_of_head_and_tail + 1;
  if(required_num_vertices > graph_num_vertices(graph)) {
    graph_resize(graph, required_num_vertices);
  }

  VERTEX* vertex = graph_vertex(graph, tail);
  vertex_add_head(vertex, head);
}

GRAPH* graph_create() {
  GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
  graph->num_vertices = 0;
  graph->vertices = (VERTEX**)calloc(0, sizeof(VERTEX*));
}

void graph_destroy(GRAPH* graph) {
  unsigned int i;
  for(i = 0; i < graph_num_vertices(graph); i++) {
    vertex_destroy(graph_vertex(graph, i));
  }
  free(graph->vertices);
  free(graph);
}

unsigned int* graph_finish_times(GRAPH* graph) {
}

GRAPH* graph_load_from_file(const char* file_path) {
  if(-1 == access(file_path, F_OK)) {
    return NULL;
  }

  if(-1 == access(file_path, R_OK)) {
    return NULL;
  }

  GRAPH* graph = graph_create();

  FILE* fp = fopen(file_path, "r");
  size_t n;
  char* row = NULL;

  while(-1 != getline(&row, &n, fp)) {
    char* saveptr = NULL;
    char* endptr = NULL;

    char* column1 = strtok_r(row, " ", &saveptr);
    char* column2 = strtok_r(NULL, " ", &saveptr);

    unsigned int tail = strtoul(column1, &endptr, 10);
    unsigned int head = strtoul(column2, &endptr, 10);

    graph_add_edge(graph, tail, head);

    free(row);
    row = NULL;
  }

  fclose(fp);

  return graph;
}

size_t graph_num_vertices(GRAPH* graph) {
  return graph->num_vertices;
}

void graph_resize(GRAPH* graph, size_t num_vertices) {
  size_t current_num_vertices = graph_num_vertices(graph);
  graph->vertices = (VERTEX**)realloc(graph->vertices, sizeof(VERTEX*) * num_vertices);
  graph->num_vertices = num_vertices;
  int i;
  for(i = current_num_vertices; i < num_vertices; i++) {
    graph->vertices[i] = vertex_create();
  }
}

GRAPH* graph_reverse(GRAPH* graph) {
  GRAPH* reverse = graph_create();
  unsigned int head_index, tail;
  for(tail = 0; tail < graph_num_vertices(graph); tail++) {
    VERTEX* vertex = graph_vertex(graph, tail);
    for(head_index = 0; head_index < vertex_num_heads(vertex); head_index++) {
      unsigned int head = vertex_head(vertex, head_index);
      graph_add_edge(reverse, head, tail);
    }
  }
  return reverse;
}

VERTEX* graph_vertex(GRAPH* graph, unsigned int tail) {
  return graph->vertices[tail];
}

VERTEX** graph_vertices(GRAPH* graph) {
  return graph->vertices;
}
