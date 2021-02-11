////////////////////////////////////////////////////////////////
// @file main_divide.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

long long int in_count = 0;
long long int out_count = 0;

graph G;

int mod = 1;
int rem = 0;

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  int i, j, k;

  mod = strtol(argv[1], 0, 10);
  rem = strtol(argv[2], 0, 10);

  while(read_graph(&G)) {

    ++in_count;

    if((in_count - 1) % mod == rem) {
      ++out_count;
      write_graph(&G);
    }
    
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

