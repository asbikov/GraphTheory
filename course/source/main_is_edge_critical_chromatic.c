////////////////////////////////////////////////////////////////
// @file main_is_edge_critical_chromatic.c
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

    int x = chromatic_number(&G);
    int is_critical = 1;
    for(i = 0; i < G.vertex_count && is_critical; ++i) {
      for(j = 0; j < i && is_critical; ++j) {
        if(is_edge(&G, i, j)) {
          remove_edge(&G, i, j);
          if(chromatic_number(&G) == x) {
            is_critical = 0;
          }
          add_edge(&G, i, j);
        }
      }
    }
    if(is_critical) {
      ++out_count;
      write_graph(&G);
    }
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}

