////////////////////////////////////////////////////////////////
// @file main_fvpq.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

long long int in_count = 0;
long long int out_count = 0;

graph G;

int p;
int q;

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  p = strtol(argv[1], 0, 10);
  q = strtol(argv[2], 0, 10);

  while(read_graph(&G)) {

    ++in_count;

    int i;

    int subset_V0[MAX_VERTEX_COUNT];
    int subset_V0_size;

    int subset_V1[MAX_VERTEX_COUNT];
    int subset_V1_size;

    uint64_t mask;

    int is_fvpq = 1;

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
      if(!find_Kn_in_subset(&G, p, subset_V0, subset_V0_size) &&
        !find_Kn_in_subset(&G, q, subset_V1, subset_V1_size) ) {
          is_fvpq = 0;
          break;
      }
    }
    if(is_fvpq) {
      ++out_count;
      write_graph(&G);
    }
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}

