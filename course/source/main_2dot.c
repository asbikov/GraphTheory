////////////////////////////////////////////////////////////////
// @file main_2dot.c
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

    int i, j;

    char filename[32];
    sprintf (filename, "g%d.dot", (int) in_count);
    FILE* file;
    file = fopen(filename, "w");
    fprintf(file, "graph {\n");
    for(i = 0; i < G.vertex_count; ++i) {
      if(vertex_degree(&G, i) == 0) {
        fprintf(file, "  %d;\n", i + 1);
      }
    }
    for(i = 1; i < G.vertex_count; ++i) {
      for(j = 0; j < i; ++j) {
        if(is_edge (&G, i, j)) {
          fprintf(file, "  %d -- %d;\n", j + 1, i + 1);
        }
      }
    }
    fprintf(file,"}\n");
    fclose(file); 
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

