#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"

#define LOAD_FACTOR 0.75

bool graph_add_vertex(GRAPH* graph, VERTEX* vertex);
bool graph_has_edge(GRAPH* graph, EDGE* edge);
bool graph_has_vertex(GRAPH* graph, VERTEX* vertex);
void graph_random_contract_edge(GRAPH* graph);

bool graph_add_edge(GRAPH* graph, EDGE* edge) {
  if(graph_has_edge(graph, edge)) {
    return false;
  }

  if(LOAD_FACTOR <= (double) graph->num_edges / graph->edge_capacity) {
    int new_capacity = graph->edge_capacity >  0 ? graph->edge_capacity * 2 : DEFAULT_EDGE_CAPACITY;
    graph->edges = (EDGE**)realloc(graph->edges, (new_capacity * sizeof(EDGE*)));
    graph->edge_capacity = new_capacity;
  }

  graph->num_edges++;
  graph->edges[graph->num_edges - 1] = edge;

  graph_add_vertex(graph, edge->left);
  graph_add_vertex(graph, edge->right);

  return true;
}

bool graph_add_vertex(GRAPH* graph, VERTEX* vertex) {
  if(graph_has_vertex(graph, vertex)) {
    return false;
  }
  if(LOAD_FACTOR <= (double) graph->num_vertices / graph->vertex_capacity) {
    int new_capacity = graph->vertex_capacity > 0 ? graph->vertex_capacity * 2 : DEFAULT_VERTEX_CAPACITY;
    graph->vertices = (VERTEX**)realloc(graph->vertices, (new_capacity * sizeof(VERTEX*)));
    graph->vertex_capacity = new_capacity;
  }
  graph->num_vertices++;
  graph->vertices[graph->num_vertices - 1] = vertex;
  return true;
}

void graph_contract_edge(GRAPH* graph, EDGE* edge) {
  int i;
  int num_deleted_edges = 0;

  VERTEX* left = edge->left;
  VERTEX* right = edge->right;
  // For all edges, replace right vertex with left vertex
  for(i = 0; i < graph->num_edges; i++) {
    EDGE* _edge = graph->edges[i];
    if(_edge->right->label == right->label) {
      _edge->right = left;
    } else if(_edge->left->label == right->label) {
      _edge->left = left;
    }
    // Close self loops
    if(_edge->left->label == _edge->right->label) {
      edge_destroy(_edge);
      _edge = NULL;
      graph->edges[i] = NULL;
      num_deleted_edges++;
    }
  }

  size_t gap_size = 0;

  for(i = 0; i < graph->num_edges; i++) {
    if(graph->edges[i] == NULL) {
      gap_size++;
    } else if(gap_size > 0) {
      graph->edges[i - gap_size] = graph->edges[i];
      graph->edges[i] = NULL;
    }
  }

  graph->num_edges -= num_deleted_edges;

  for(i = 0; i < graph->num_vertices; i++) {
    VERTEX* _vertex = graph->vertices[i];
    bool is_deleted = false;
    if(is_deleted) {
      graph->vertices[i-1] = graph->vertices[i];
      graph->vertices[i] = NULL;
    } else if(_vertex->label == right->label) {
      vertex_destroy(_vertex);
      graph->vertices[i] == NULL;
      is_deleted = true;
    }
  }

  graph->num_vertices--;
}

GRAPH* graph_copy(GRAPH* graph) {
  GRAPH* _graph = graph_create(graph->num_vertices, graph->num_edges, 1.1);
  int i;
  for(i = 0; i < graph->num_edges; i++) {
    graph_add_edge(_graph, edge_copy(graph->edges[i]));
  }
  return _graph;
}

GRAPH* graph_create(size_t vertex_capacity, size_t edge_capacity, double load_factor) {
  GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));

  graph->edges = (EDGE**)malloc(edge_capacity * sizeof(EDGE*));
  graph->edge_capacity = edge_capacity;
  graph->num_edges = 0;

  graph->vertices = (VERTEX**)malloc(vertex_capacity * sizeof(VERTEX*));
  graph->vertex_capacity = vertex_capacity;
  graph->num_vertices = 0;

  graph->load_factor = load_factor;

  return graph;
}

void graph_destroy(GRAPH* graph) {
  free(graph);
}

int graph_find_min_cut(GRAPH* graph) {
  srand(time(NULL));
  int min_cut = graph->num_vertices;
  int times = graph->num_vertices;
  int i;
  for(i = 0; i < times; i++) {
    GRAPH* _graph = graph_copy(graph);
    while(_graph->num_vertices > 2) {
      graph_random_contract_edge(_graph);
    }
    if(_graph->num_edges < min_cut) {
      min_cut = _graph->num_edges;
    }
    graph_destroy(_graph);
  }
  return min_cut;
}

VERTEX* graph_get_vertex(GRAPH* graph, int label) {
  int i;
  for(i = 0; i < graph->num_vertices; i++) {
    if(graph->vertices[i]->label == label) {
      return graph->vertices[i];
    }
  }
  return NULL;
}

bool graph_has_edge(GRAPH* graph, EDGE* edge) {
  int i;
  for(i = 0; i < graph->num_edges; i++) {
    EDGE* _edge = graph->edges[i];
    if(_edge->left->label == edge->left->label
        && _edge->right->label == edge->right->label) {
      return true;
    }
  }
  return false;
}

bool graph_has_vertex(GRAPH* graph, VERTEX* vertex) {
  return NULL != graph_get_vertex(graph, vertex->label);
}
 
GRAPH* graph_load_from_file(const char* file_path) {
  GRAPH* graph = graph_create(DEFAULT_VERTEX_CAPACITY, DEFAULT_EDGE_CAPACITY, DEFAULT_LOAD_FACTOR);
  FILE* fp = fopen(file_path, "r");
  char* line = NULL;
  char* copy = NULL;
  size_t n = 0;
  while((line = fgetln(fp, &n)) != NULL) {
    copy = malloc(sizeof(char) * n + 1);
    memcpy(copy, line, n);
    copy[n] = '\0';
    char* context = NULL;
    VERTEX* vertex = vertex_tokenize(copy, "\t", &context);
    VERTEX* adjacent_vertex = NULL;
    while(NULL != (adjacent_vertex = vertex_tokenize(NULL, "\t", &context))) {
      EDGE* edge = edge_create(vertex, adjacent_vertex);
      if (edge != NULL) {
        graph_add_edge(graph, edge_create(vertex, adjacent_vertex));
      }
    }
    free(copy);
    copy = NULL;
  }
  fclose(fp);
  return graph;
}

void graph_random_contract_edge(GRAPH* graph) {
  int edge_index = rand() % graph->num_edges;
  graph_contract_edge(graph, graph->edges[edge_index]);
}
