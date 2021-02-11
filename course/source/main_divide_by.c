////////////////////////////////////////////////////////////////
// @file main_divide_by.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

#define MAX_CONSTRAINTS_COUNT 1024

#define MAX_VALUES_COUNT 1024

long long int in_count = 0;
long long int out_count = 0;

graph G;

int values[MAX_VALUES_COUNT];
int values_count = 0;
int graphs_per_value[MAX_VALUES_COUNT];

FILE *files[MAX_VALUES_COUNT];

char *prefix = NULL;

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_V(const graph *G) {
  return G->vertex_count;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_E(const graph *G) {
  return count_edges(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_d(const graph *G) {
  return min_degree(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_D(const graph *G) {
  return max_degree(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_w(const graph *G) {
  return clique_number(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_a(const graph *G) {
  return independence_number(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_x(const graph *G) {
  return chromatic_number(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraint_connected_components(const graph *G) {
  return count_connected_components(G);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int (*constraints[]) (const graph *G) = {
  constraint_V,
  constraint_E,
  constraint_d,
  constraint_D,
  constraint_w,
  constraint_a,
  constraint_x,
  constraint_connected_components,
};

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
const char *constraint_names[] = {
  "-V",
  "-E",
  "-d",
  "-D",
  "-w",
  "-a",
  "-x",
  "-connected_components",
};

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int constraints_count = sizeof(constraint_names) / sizeof(char *);

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int index_of_constraint(const char *constraint_name) {
  int result = -1;
  int i;
  for(i = 0; i < constraints_count; ++i) {
    if(!strcmp(constraint_name, constraint_names[i])) {
      result = i;
      break;
    }
  }
  return result;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
void add_graph(const graph *G, int value) {
  int i;
  for(i = 0; i < values_count; ++i) {
    if(values[i] == value) {
      ++graphs_per_value[i];
      if(prefix) {
        write_graph_file(G, files[i]);
      }
      break;
    }
  }
  if(i == values_count) {
    values[i] = value;
    graphs_per_value[i] = 1;
    ++values_count;
    if(prefix) {
      char filename[256];
      strcpy(filename, prefix);
      strcat(filename, "_");
      sprintf(filename + strlen(filename), "%d", value);
      files[i] = fopen(filename, "wb");
      write_graph_file(G, files[i]);
    }
  }
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
void write_output() {
  int i, j;
  int sorted_values[MAX_VALUES_COUNT];
  for(i = 0; i < values_count; ++i) {
    sorted_values[i] = i;
  }
  for(i = 0; i < values_count; ++i) {
    for(j = i + 1; j < values_count; ++j) {
      if(values[sorted_values[j]] < values[sorted_values[i]]) {
        int swap = sorted_values[i];
        sorted_values[i] = sorted_values[j];
        sorted_values[j] = swap;
      }
    }
  }
  for(i = 0; i < values_count; ++i) {
    fprintf(stdout, "%d %d\n", values[sorted_values[i]], graphs_per_value[sorted_values[i]]);
  }
  for(i = 0; i < values_count; ++i) {
    fclose(files[i]);
  }
}

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  int i;

  int (*arg_constraint) (const graph *G);

  i = 1;
  if(argc > 1 && !strcmp(argv[1], "-prefix")) {
    prefix = argv[2];
    i = 3;
  }

  for(i; i < argc; ++i) {
    int index = index_of_constraint(argv[i]);
    if(index == -1) {
      fprintf(stderr, "Usage:\ndivide_by [-prefix value] [-constraint value] ...\n");
      return 1;
    }
    arg_constraint = constraints[index];
    ++i;
  }

  while(read_graph(&G)) {

    ++in_count;

    int value = arg_constraint(&G);
    
    add_graph(&G, value);
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "\n");

  write_output();

  return 0;
}

