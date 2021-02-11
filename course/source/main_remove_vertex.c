////////////////////////////////////////////////////////////////
// @file main_remove_vertex.c
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

  int i, j, k;

  while(read_graph(&G)) {

    ++in_count;

    graph G_copy;

    for(i = 0; i < G.vertex_count; ++i) {
      G_copy = G;
      remove_vertex(&G_copy, i);
      ++out_count;
      write_graph(&G_copy);
    }
    
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

