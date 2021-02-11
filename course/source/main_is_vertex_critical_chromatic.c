////////////////////////////////////////////////////////////////
// @file main_is_vertex_critical_chromatic.c
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

  int i;

  while(read_graph(&G)) {

    ++in_count;

    graph G_copy;
    int x = chromatic_number(&G);
    int is_critical = 1;
    for(i = 0; i < G.vertex_count; ++i) {
      G_copy = G;
      remove_vertex(&G_copy, i);
      if(chromatic_number(&G_copy) == x) {
        is_critical = 0;
        break;
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

