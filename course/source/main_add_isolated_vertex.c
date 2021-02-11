////////////////////////////////////////////////////////////////
// @file main_add_isolated_vertex.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

long long int in_count = 0;
long long int out_count = 0;

graph G;

graph G_extended;


////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  while(read_graph(&G)) {

    ++in_count;

    ++G.vertex_count;

    ++out_count;
    write_graph(&G);

  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

