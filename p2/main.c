#define PIVOT_FIRST 1
#define PIVOT_LAST 2
#define PIVOT_MEDIAN 3

#include <stdio.h>
#include <stdlib.h>
#include  "pivot.h"
#if PIVOT_TYPE==PIVOT_FIRST
  #include "pivot_first.c"
#elif PIVOT_TYPE==PIVOT_LAST
  #include "pivot_last.c"
#elif PIVOT_TYPE==PIVOT_MEDIAN
  #include "pivot_median.c"
#endif

int partition(int *input, size_t size, int pivot_index);
void swap(int *input, int i, int j);

void quicksort(int *input, size_t size, int *comparisons) {
  if(size <= 1) {
    return;
  }

  *comparisons += size - 1;

  int pivot_index = choose_pivot_index(input, size);
  int partition_index = partition(input, size, pivot_index);

  quicksort(input, partition_index, comparisons);
  quicksort(input + partition_index + 1, size - (partition_index + 1), comparisons);
}

int partition(int *input, size_t size, int pivot_index) {
  int pivot = input[pivot_index];
  int index = 1;
  int partition_index = 1;

  swap(input, 0, pivot_index);

  for(; index < size; index++) {
    if(input[index] < pivot) {
      swap(input, index, partition_index);
      partition_index++;
    }
  }

  swap(input, 0, --partition_index);

  return partition_index;
}

void swap(int *input, int i, int j) {
  if(i == j || i < 0 || j < 0) {
    return;
  }
  int temp = input[i];
  input[i] = input[j];
  input[j] = temp;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    printf("Illegal number of args.\n");
  }

  char * file_path = argv[1];
  long size = strtol(argv[2], NULL, 0); 

  printf("Reading %s of length %lu\n", file_path, size);

  int input[size];
  FILE *fp = fopen(file_path, "r");
  char *line = NULL;
  int lines_read = 0;
  size_t line_size;
  while(-1 != getline(&line, &line_size, fp)) {
    input[lines_read] = (int) strtol(line, NULL, 0);
    free(line);
    line = NULL;
    lines_read++;
  }
  fclose(fp);

  printf("Read %d lines\n", lines_read);

  int comparisons = 0;
  quicksort(input, size, &comparisons);

  printf("Made %d comparisons\n", comparisons);
}
