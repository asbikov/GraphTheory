////////////////////////////////////////////////////////////////
// @file main_add_vertex_ramsey_p_q.c
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

  int p = strtol(argv[1], 0, 10);
  int q = strtol(argv[2], 0, 10);

  int selected_vertices[MAX_VERTEX_COUNT];
  int selected_vertices_size;
  int not_selected_vertices[MAX_VERTEX_COUNT];
  int not_selected_vertices_size;

  while(read_graph(&G)) {

    ++in_count;

    uint64_t mask;
    for(mask = 0; mask < ((uint64_t)1 << G.vertex_count); ++mask) {
      selected_vertices_size = 0;
      not_selected_vertices_size = 0;
      for(i = 0; i < G.vertex_count; ++i) {
        if(mask & ((uint64_t)1 << i)) {
          selected_vertices[selected_vertices_size++] = i;
        }
        else {
          not_selected_vertices[not_selected_vertices_size++] = i;
        }
      }
      if(!find_Kn_in_subset(&G, p - 1, selected_vertices, selected_vertices_size) &&
        !find_In_in_subset(&G, q - 1, not_selected_vertices, not_selected_vertices_size)) {
        G_extended = G;
        add_vertex(&G_extended, selected_vertices, selected_vertices_size);
        ++out_count;
        write_graph(&G_extended);
      }
    }

  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

