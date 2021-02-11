////////////////////////////////////////////////////////////////
// @file main_fv33.c
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

  while(read_graph(&G)) {

    ++in_count;

    int i;

    int subset_V0[MAX_VERTEX_COUNT];
    int subset_V0_size;

    int subset_V1[MAX_VERTEX_COUNT];
    int subset_V1_size;

    uint64_t mask;

    int is_fv33 = 1;

    for(mask = 0; mask < ((uint64_t)1 << G.vertex_count); ++mask) {
      subset_V0_size = 0;
      subset_V1_size = 0;
      for(i = 0; i < G.vertex_count; ++i) {
        if(mask & ((uint64_t)1 << i)) {
          subset_V0[subset_V0_size++] = i;
        }
        else {
          subset_V1[subset_V1_size++] = i;
        }
      }
      if(!find_Kn_in_subset(&G, 3, subset_V0, subset_V0_size) &&
        !find_Kn_in_subset(&G, 3, subset_V1, subset_V1_size) ) {
        is_fv33 = 0;
        break;
      }
    }
    if(is_fv33) {
      ++out_count;
      write_graph(&G);
    }
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

