#include <stdio.h>

int median(int*, int, int, int);

int choose_pivot_index(int *input, size_t size) {
  int first = 0, last = size - 1, middle;

  if(size % 2 == 0) {
    middle = (size / 2) - 1;
  }
  else {
    middle = (size - 1) / 2;
  }

  return median(input, first, last, middle);
}

int median(int *input, int a, int b, int c) {
  int ab_min, ab_max;
  if(input[a] < input[b]) {
    ab_min = a;
    ab_max = b;
  } else {
    ab_min = b;
    ab_max = a;
  }

  if(input[c] < input[ab_max]) {
    if(input[ab_min] < input[c]) {
      return c;
    }
    return ab_min;
  }

  return ab_max;
}
