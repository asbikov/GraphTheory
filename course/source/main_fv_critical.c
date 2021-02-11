////////////////////////////////////////////////////////////////
// @file main_fv_critical.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

#define MAX_S 8

long long int in_count = 0;
long long int out_count = 0;

graph G;

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_fv_coloring(
  const graph *G,
  const int a[MAX_S],
  int s,
  int colors[MAX_VERTEX_COUNT],
  int vertex_index
  ) {

  if(vertex_index == G->vertex_count) {
    return 1;
  }

  int i, j;

  int neighbors[MAX_VERTEX_COUNT];
  int neighbors_count = 0;
  for(i = 0; i < vertex_index; ++i) {
    if(is_edge(G, vertex_index, i)) {
      neighbors[neighbors_count++] = i;
    }
  }

  for(i = 0; i < s; ++i) {
    int neighbors_in_color_i[MAX_VERTEX_COUNT];
    int neighbors_in_color_i_count = 0;

    for(j = 0; j < neighbors_count; ++j) {
      if(colors[neighbors[j]] == i) {
        neighbors_in_color_i[neighbors_in_color_i_count++] = neighbors[j];
      }
    }

    int can_color_in_color_i = !find_Kn_in_subset(G, a[i] - 1, neighbors_in_color_i, neighbors_in_color_i_count);
    
    if(can_color_in_color_i) {
      colors[vertex_index] = i;
      if(find_fv_coloring(G, a, s, colors, vertex_index + 1)) {
        return 1;
      }
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_fv(
  const graph *G,
  const int a[MAX_S],
  int s
  ) {
  int colors[MAX_VERTEX_COUNT];
  int result = !find_fv_coloring(G, a, s, colors, 0);
  return result;
}

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  int i, j;

  int a[MAX_S];
  int s;
  
  s = argc - 1;
  for(i = 0; i < s; ++i) {
    a[i] = strtol(argv[i + 1], 0, 10);
  }

  while(read_graph(&G)) {

    ++in_count;

    if(is_fv(&G, a, s)) {
      int is_critical = 1;

      if(min_degree(&G) == 0) {
        is_critical = 0;
      }

      for(i = 0; i < G.vertex_count && is_critical; ++i) {
        for(j = 0; j < i && is_critical; ++j) {
          if(is_edge(&G, i, j)) {
            remove_edge(&G, i, j);
            if(is_fv(&G, a, s)) {
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
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

