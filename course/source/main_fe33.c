////////////////////////////////////////////////////////////////
// @file main_fe33.c
// @brief A sample application.
////////////////////////////////////////////////////////////////

#include "graph.h"

#define MAX_S 8

#define MAX_TRIANGLES_COUNT (MAX_VERTEX_COUNT*(MAX_VERTEX_COUNT-1)*(MAX_VERTEX_COUNT-2)/6)

long long int in_count = 0;
long long int out_count = 0;

graph G;

typedef int edge[2];
typedef int triangle[3];

edge edges[MAX_EDGES_COUNT];
int edges_count;
int edge_indices[MAX_VERTEX_COUNT][MAX_VERTEX_COUNT];
triangle triangles[MAX_TRIANGLES_COUNT];
int triangles_count;
int triangles_for_edge[MAX_EDGES_COUNT][MAX_VERTEX_COUNT];
int triangles_for_edge_count[MAX_EDGES_COUNT];

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_triangle(const graph *G, int i, int j, int k) {
  return (is_edge(G, i, j) && is_edge(G, j, k) && is_edge(G, k, i));
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
void find_triangles() {
  int i, j, k;
  edges_count = 0;
  for(i = 1; i < G.vertex_count; ++i) {
    for(j = 0; j < i; ++j) {
      if(is_edge(&G, i, j)) {
        edge_indices[i][j] = edges_count;
        edge_indices[j][i] = edges_count;
        edges[edges_count][0] = i;
        edges[edges_count][1] = j;
        triangles_for_edge_count[edges_count] = 0;
        ++edges_count;
      }
    }
  }
  triangle *p_triangle;
  triangles_count = 0;
  for(i = 2; i < G.vertex_count; ++i) {
    for(j = 1; j < i; ++j) {
      for(k = 0; k < j; ++k) {
        if (is_triangle(&G, i, j, k)) {
          p_triangle = &(triangles[triangles_count]);
          (*p_triangle)[0] = edge_indices[i][j];
          (*p_triangle)[1] = edge_indices[j][k];
          (*p_triangle)[2] = edge_indices[k][i];
          triangles_for_edge[(*p_triangle)[0]]
          [triangles_for_edge_count[(*p_triangle)[0]]] =
            triangles_count;
          triangles_for_edge[(*p_triangle)[1]]
          [triangles_for_edge_count[(*p_triangle)[1]]] =
            triangles_count;
          triangles_for_edge[(*p_triangle)[2]]
          [triangles_for_edge_count[(*p_triangle)[2]]] =
            triangles_count;
          ++triangles_for_edge_count[(*p_triangle)[0]];
          ++triangles_for_edge_count[(*p_triangle)[1]];
          ++triangles_for_edge_count[(*p_triangle)[2]];
          ++triangles_count;
        }
      }
    }
  }
}



////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_fe33_coloring(
  const graph *G,
  int colors[MAX_EDGES_COUNT],
  int edge_index
  ) {
  if(edge_index == edges_count) {
    return 1;
  }

  int i, j;


  for(i = 0; i < 2; ++i) {
    // the two colors are 1 and -1
    int can_color_in_color_i = 1;
    for(j = 0; j < triangles_for_edge_count[edge_index] && can_color_in_color_i; ++j) {
      triangle *t = &(triangles[triangles_for_edge[edge_index][j]]);
      int color_0 = colors[(*t)[0]]; 
      int color_1 = colors[(*t)[1]]; 
      int color_2 = colors[(*t)[2]];

      if(i == 0) {
        can_color_in_color_i = !(color_0 + color_1 + color_2 == 2);
      }

      if(i == 1) {
        can_color_in_color_i = !(color_0 + color_1 + color_2 == -2);
      }
    }
    if(can_color_in_color_i) {
      colors[edge_index] = (i == 0) ? 1 : -1;
      int result = find_fe33_coloring(G, colors, edge_index + 1);
      colors[edge_index] = 0;
      if(result) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_fe33(const graph *G) {
  find_triangles();

  int colors[MAX_EDGES_COUNT];
  memset(colors, 0, edges_count * sizeof(int));
  int result = !find_fe33_coloring(G, colors, 0);
  return result;
}

////////////////////////////////////////////////////////////////
// Entry point for the application.
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  while(read_graph(&G)) {

    ++in_count;

    if(is_fe33(&G)) {
      ++out_count;
      write_graph(&G);
    }
  }

  fprintf(stderr, "in : %lld\n", in_count);

  fprintf(stderr, "out: %lld\n", out_count);
  
  fprintf(stderr, "\n");

  return 0;
}

