////////////////////////////////////////////////////////////////
// @file main_add_vertex.c
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

  int i;

  int subset[MAX_VERTEX_COUNT];
  int subset_size;

  while(read_graph(&G)) {

    ++in_count;

    uint64_t mask;
    for(mask = 0; mask < ((uint64_t)1 << G.vertex_count); ++mask) {
      subset_size = 0;
      for(i = 0; i < G.vertex_count; ++i) {
        if(mask & ((uint64_t)1 << i)) {
          subset[subset_size++] = i;
        }
      }
      G_extended = G;
      add_vertex(&G_extended, subset, subset_size);
      ++out_count;
      write_graph(&G_extended);
    }

  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

