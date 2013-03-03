#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
  int i;
  char* endptr;
  int times = strtol(argv[1], &endptr, 10);
  for(i = 0; i < times; i++) {
    printf("%i\n", (int) rand() % 3);
  }
  return 0;
}
