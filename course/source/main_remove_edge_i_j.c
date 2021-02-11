////////////////////////////////////////////////////////////////
// @file main_remove_edge_i_j.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

long long int in_count = 0;
long long int out_count = 0;

graph G;

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  int i = strtol(argv[1], 0, 10);
  int j = strtol(argv[2], 0, 10);

  while(read_graph(&G)) {

    ++in_count;

    remove_edge(&G, i, j);

    ++out_count;

    write_graph(&G);
    
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}
