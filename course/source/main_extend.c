////////////////////////////////////////////////////////////////
// @file main_extend.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

#define MAX_SUBSETS_COUNT 1 << 16
long long int in_count = 0;
long long int out_count = 0;

graph G;

graph G_extended;

int q;

int r;

int max_subsets[MAX_SUBSETS_COUNT][MAX_VERTEX_COUNT];
int max_subset_sizes[MAX_SUBSETS_COUNT];
int max_subsets_count;

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////
void find_max_subsets() {
  max_subsets_count = 0;

  int i, j;

  int subset[MAX_VERTEX_COUNT];
  int subset_size;

  uint64_t mask;
  for(mask = 0; mask < ((uint64_t)1 << G.vertex_count); ++mask) {
    subset_size = 0;
    for(i = 0; i < G.vertex_count; ++i) {
      if(mask & ((uint64_t)1 << i)) {
        subset[subset_size++] = i;
      }
    }
    if(is_max_Kn_free_subset(&G, q - 1, subset, subset_size)) {
      memcpy(max_subsets[max_subsets_count], subset, subset_size * sizeof(int));
      max_subset_sizes[max_subsets_count] = subset_size;
      ++max_subsets_count;
    }
  }
}

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////
void extend_graph_worker(int added_vertices_count) {
  if(added_vertices_count == r) {
    if(check_edge_adds_kn(&G_extended, q)) {
      ++out_count;
      write_graph(&G_extended);
    }
    return;
  }
  int i;
  for(i = 0; i < max_subsets_count; ++i) {
    add_vertex(&G_extended, max_subsets[i], max_subset_sizes[i]);
    extend_graph_worker(added_vertices_count + 1);
    remove_vertex(&G_extended, G.vertex_count + added_vertices_count);
  }

}

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////
void extend_graph() {
  G_extended = G;
  extend_graph_worker(0);
}


////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  q = strtol(argv[1], 0, 10);
  r = strtol(argv[2], 0, 10);

  while(read_graph(&G)) {

    ++in_count;

    find_max_subsets();

    extend_graph();

  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}

