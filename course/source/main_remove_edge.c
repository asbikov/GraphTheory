////////////////////////////////////////////////////////////////
// @file main_remove_edge.c
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

  int i, j;

  while(read_graph(&G)) {

    ++in_count;

    for(i = 1; i < G.vertex_count; ++i) {
      for(j = 0; j < i; ++j) {
        if(is_edge(&G, i, j)) {
          remove_edge(&G, i, j);
          ++out_count;
          write_graph(&G);
          add_edge(&G, i, j);
        }
      }
    }
    
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}


