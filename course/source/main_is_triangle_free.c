////////////////////////////////////////////////////////////////
// @file main_is_triangle_free.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

long long int in_count = 0;
long long int out_count = 0;

graph G;

////////////////////////////////////////////////////////////////
// Checks if the vertices with indeces i, j, k form a triangle in G.
////////////////////////////////////////////////////////////////
int is_K3(const graph *G, int i, int j, int k) {
  int result = is_edge(G, i, j) && is_edge(G, j, k) && is_edge(G, k, i);
}

////////////////////////////////////////////////////////////////
// Checks if there is a triangle in G.
////////////////////////////////////////////////////////////////
int check_for_K3(const graph *G) {
  int i, j, k;
  for(i = 2; i < G->vertex_count; ++i) {
    for(j = 1; j < i; ++j) {
      if(is_edge(G, i, j)) {
        for(k = 0; k < j; ++k) {
          if(is_edge(G, j, k) && is_edge(G, k, i)) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  int i, j;

  while(read_graph(&G)) {

    ++in_count;

    if(!check_for_K3(&G)) {
      ++out_count;
      write_graph(&G);
    }
    
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);

  fprintf(stderr, "\n");

  return 0;
}

