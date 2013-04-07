#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "graph.h"
#include "vertex.h"

#define GRAPH_INITIAL_CAPACITY 10

struct Graph {
  size_t capacity;
  size_t num_vertices;
  Vertex** vertices;
};

size_t graph_capacity(Graph* graph) {
  return graph->capacity;
}

Graph* graph_create() {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->capacity = GRAPH_INITIAL_CAPACITY;
  graph->num_vertices = 0;
  graph->vertices = (Vertex**)calloc(GRAPH_INITIAL_CAPACITY, sizeof(Vertex*));
  return graph;
}

Vertex* graph_vertex(Graph* graph, unsigned int label) {
  return graph->vertices[label];
}

void graph_destroy(Graph* graph) {
  int i;
  for(i = 0; i < (int)graph_num_vertices(graph) - 1; i++) {
    free(graph_vertex(graph, i));
  }
  free(graph->vertices);
}

Graph* graph_load_from_file(const char* file_path) {
  Graph* graph = graph_create();

  if(access(file_path, F_OK) != 0) {
    return NULL;
  }

  if(access(file_path, R_OK) != 0) {
    return NULL;
  }

  FILE* fp = fopen(file_path, "r");
  char* line = NULL;
  size_t n = 0;

  while(-1 != getline(&line, &n, fp)) {
    char* save0 = NULL; 
    char* save1 = NULL;

    unsigned int tail = atoi(strtok_r(line, "\t", &save0));

    char* edge = NULL;
    while(NULL != (edge = strtok_r(NULL, "\t\n", &save0))) {
      unsigned int head = atoi(strtok_r(edge, ",", &save1));
      unsigned int length = atoi(strtok_r(NULL, ",", &save1));
      graph_add_edge(graph, tail, head, length);
    }

    free(line);
    line = NULL;
  }

  return graph;
}

void graph_resize(Graph* graph, size_t min_size) {
  size_t capacity = graph_capacity(graph);
  size_t new_capacity = min_size > capacity ? min_size * 2 : capacity * 2;

  graph->vertices = (Vertex**)realloc(graph->vertices, sizeof(Vertex*) * new_capacity);

  int i;
  for(i = capacity; i < new_capacity; i++) {
    graph->vertices[i] = NULL;
  }

  graph->capacity = new_capacity;
}

size_t graph_num_vertices(Graph* graph) {
  return graph->num_vertices;
}

bool graph_has_vertex(Graph* graph, unsigned int label) {
  return graph_vertex(graph, label) != NULL;
}

void graph_add_vertex(Graph* graph, unsigned int label) {
  if(graph_capacity(graph) < label + 1) {
    graph_resize(graph, label + 1);
  }

  if(graph_has_vertex(graph, label)) {
    return;
  }

  Vertex* vertex = vertex_create(label);
  graph->vertices[label] = vertex;

  graph->num_vertices++;
}

void graph_add_edge(Graph* graph, unsigned int tail, unsigned int head, unsigned int length) {
  graph_add_vertex(graph, tail);
  graph_add_vertex(graph, head);

  Vertex* vertex = graph_vertex(graph, tail);
  Vertex* head_vertex = graph_vertex(graph, head);
  vertex_add_edge(vertex, head_vertex, length);
}

