#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long count_split_inversions(int *left_input, size_t left_size, int* right_input, size_t right_size, int** output) {
  unsigned long inversions = 0;
  int index = 0;
  int left_index = 0;
  int right_index = 0;

  if(*output == NULL) {
    *output = (int*)malloc(sizeof(int) * (left_size + right_size));
  }

  while(left_index < left_size && right_index < right_size) {
    if(left_input[left_index] < right_input[right_index]) {
      (*output)[index] = left_input[left_index];
      left_index++;
    } else {
      (*output)[index] = right_input[right_index];
      inversions += left_size - left_index;
      right_index++;
    }
    index++;
  }

  for(; right_index < right_size; right_index++) {
    (*output)[index] = right_input[right_index];
    index++;
  }

  for(; left_index < left_size; left_index++) {
    (*output)[index] = left_input[left_index];
    index++;
  }

  return inversions;
}

unsigned long count_inversions(int* input, size_t size, int** output) {
  if(size >= 2) {
    int left_size = 0;
    int right_size = 0;

    if(size % 2 == 0) {
      left_size = size / 2;
      right_size = left_size;
    } else {
      left_size = (size - 1) / 2;
      right_size = left_size + 1;
    }

    int* left_output = (int*)malloc(sizeof(int) * left_size);
    int* right_output = (int*)malloc(sizeof(int) * right_size);

    long left_inversions = count_inversions(input, left_size, &left_output);
    unsigned long right_inversions = count_inversions(input + left_size, right_size, &right_output);
    unsigned long split_inversions = count_split_inversions(left_output, left_size, right_output, right_size, output);

    free(left_output);
    free(right_output);

    return left_inversions + right_inversions + split_inversions;
  }

  if(size == 0) {
    return -1;
  }

  if(size == 1) {
    **output = *input;
    return 0;
  }
}

int main(int argc, char** argv) {
  if(argc < 3) {
    exit(EXIT_FAILURE);
  }

  const char* file_path = argv[1];
  char *p;
  int num_lines = atoi(argv[2]);
  int errno = 0;

  // Sanity checks
  errno = access(file_path, F_OK);
  if(0 != errno) {
    printf("File does not exist\n");
    exit(EXIT_FAILURE);
  }

  errno = access(file_path, R_OK);
  if(0 != errno) {
    printf("Cannot read file\n");
    exit(EXIT_FAILURE);
  }

  // Initialize array
  int input[num_lines];

  // Open and read file
  FILE *file = fopen(file_path, "r");
  char *line = NULL;
  int lines_read = 0;
  size_t len = 0;
  printf("Reading input %s of size %i\n", file_path, num_lines);
  while(-1 != getline(&line, &len, file)) {
    input[lines_read] = atoi(line);
    free(line);
    line = NULL;
    lines_read++;
    if(lines_read == num_lines) {
      break;
    }
  }
  printf("Read %d lines\n", lines_read);

  int* output = NULL;
  unsigned long inversions = count_inversions(input, num_lines, &output);
  printf("Counted %lu inversions\n", inversions);
  fclose(file);
  return 0;
}
