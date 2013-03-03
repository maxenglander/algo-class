#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"

void usage(const char* executable_name);

void check(bool condition, const char* executable_name, const char* message) {
  if(!condition) {
    usage(executable_name);
    if(message != NULL) {
      printf("\t%s\n", message);
    }
    exit(EXIT_FAILURE);
  }
}

bool is_readable(const char* file_path) {
  return 0 == access(file_path, F_OK | R_OK);  
}



void usage(const char* executable_name) {
  printf("%s <file>\n", executable_name);
}

int main(int argc, char** argv) {
  check(argc == 2, argv[0], NULL);
  check(is_readable(argv[1]), argv[0], "file is not readable");
  GRAPH* graph = graph_load_from_file(argv[1]);
  int min_cut = graph_find_min_cut(graph);
  printf("Min cut: %i\n", min_cut);
  graph_destroy(graph);
  return 0;
}

