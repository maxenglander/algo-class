#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "edge.h"
#include "graph_search.h"
#include "iterator.h"

#define GRAPH_SEARCH_STATE_UNEXPLORED 0
#define GRAPH_SEARCH_STATE_EXPLORING 1
#define GRAPH_SEARCH_STATE_EXPLORED 2

struct GraphSearch {
  char* states;
  size_t num_paths;
  unsigned int* shortest_paths;
};

GraphSearch* graph_search_create(Graph* graph) {
  GraphSearch* graph_search = (GraphSearch*)malloc(sizeof(GraphSearch));
  graph_search->num_paths = graph_num_vertices(graph);
  graph_search->states = (char*)calloc(graph_num_vertices(graph), sizeof(char));
  graph_search->shortest_paths = (unsigned int*)calloc(graph_num_vertices(graph), sizeof(unsigned int));

  unsigned int i;
  for(i = 0; i < graph_search->num_paths; i++) {
    graph_search->shortest_paths[i] = UINT_MAX;
    graph_search->states[i] = GRAPH_SEARCH_STATE_UNEXPLORED;
  }

  return graph_search;
}

void graph_search_destroy(GraphSearch* graph_search) {
  free(graph_search->shortest_paths);
  free(graph_search);
}

size_t graph_search_num_paths(GraphSearch* graph_search) {
  return graph_search->num_paths;
}

void _graph_search_find_shortest_paths(GraphSearch* graph_search, List* exploring) {
  List* _exploring = list_create();
  Vertex* next_vertex = NULL;
  unsigned int shortest_distance = UINT_MAX;

  // For each vertex v that we are in the process of exploring
  while(!list_empty(exploring)) {
    Vertex* tail = list_pop(exploring);
    bool tail_has_unexplored_heads = false;

    if(!vertex_has_edges(tail)) {
      graph_search->states[vertex_label(tail)] = GRAPH_SEARCH_STATE_EXPLORED; 
      continue;
    }

    Iterator* iterator = list_iterator(vertex_edges(tail));

    // For each head w in v
    while(iterator_has_next(iterator)) {
      Edge* edge = (Edge*)iterator_next(iterator);
      Vertex* head = edge_vertex(edge);

      // If w is unexplored
      if(GRAPH_SEARCH_STATE_UNEXPLORED == graph_search->states[vertex_label(head)]) {
        tail_has_unexplored_heads = true;
        unsigned int distance = graph_search->shortest_paths[vertex_label(tail)] + edge_length(edge);
        
        // Set w as the next vertex if w is the closest to the source
        if(next_vertex == NULL || distance < shortest_distance) {
          next_vertex = head;
          shortest_distance = distance;
        }
      }
    }

    iterator_destroy(iterator);

    // If v has unexplored heads
    if(tail_has_unexplored_heads) {
      // Keep v in the list of vertices we are exploring
      list_push(_exploring, tail);
    } else {
      // Mark v as fully explored
      graph_search->states[vertex_label(tail)] = GRAPH_SEARCH_STATE_EXPLORED; 
    }
  }

  // Add the closest-to-source w to list of vertices we are exploring
  if(next_vertex != NULL) {
    graph_search->states[vertex_label(next_vertex)] = GRAPH_SEARCH_STATE_EXPLORING;
    graph_search->shortest_paths[vertex_label(next_vertex)] = shortest_distance;
    list_push(_exploring, next_vertex);
  }

  // Continue exploring shortest paths
  if(!list_empty(_exploring)) {
    _graph_search_find_shortest_paths(graph_search, _exploring);
  }

  free(_exploring);
}

void graph_search_find_shortest_paths(GraphSearch* graph_search, Vertex* source) {
  graph_search->shortest_paths[vertex_label(source)] = 0;
  graph_search->states[vertex_label(source)] = GRAPH_SEARCH_STATE_EXPLORING;

  List* exploring = list_create();
  list_push(exploring, source);
  _graph_search_find_shortest_paths(graph_search, exploring);
  list_destroy(exploring);
}

unsigned int graph_search_shortest_path(GraphSearch* graph_search, Vertex* target) {
  return graph_search->shortest_paths[vertex_label(target)];
}
