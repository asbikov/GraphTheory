////////////////////////////////////////////////////////////////
// @file coloring.h
// @brief Implementations of functions related to colorings.
////////////////////////////////////////////////////////////////

#include "graph.h"


////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_n_coloring_worker(const graph *G, int n, int colors[MAX_VERTEX_COUNT], int vertex_index) {
  int i, j;
  if (vertex_index == G->vertex_count) {
    return 1;
  }
  int neighbors[MAX_VERTEX_COUNT];
  int neighbors_count = 0;
  for (i = 0; i < vertex_index; ++i) {
    if (is_edge(G, i, vertex_index)) {
      neighbors[neighbors_count++] = i;
    }
  }
  for (i = 0; i < n; ++i) {
    int can_color = 1;
    for (j = 0; j < neighbors_count; ++j) {
      if (colors[neighbors[j]] == i) {
        can_color = 0;
        break;
      }
    }
    if (can_color) {
      colors[vertex_index] = i;
      if (find_n_coloring_worker(G, n, colors, vertex_index + 1)) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_n_coloring(const graph *G, int n) {
  int colors[MAX_VERTEX_COUNT];
  colors[0] = 0;
  return find_n_coloring_worker(G, n, colors, 1);
}


////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_n_coloring_iterative(const graph *G, int n) {
  int colors[MAX_VERTEX_COUNT];
  int i, j;

  int vertex_index = 0;

  for(i = 0; i < G->vertex_count; ++i) {
    colors[i] = -1;
  }

  colors[vertex_index] = 0;

  ++vertex_index;

  while(vertex_index >= 1 && vertex_index < G->vertex_count) {

    for(i = colors[vertex_index] + 1; i < n; ++i) {
      for(j = 0; j < vertex_index; ++j) {
        if(colors[j] == i && is_edge(G, j, vertex_index)) {
          break;
        }
      }
      if(j == vertex_index) {
        colors[vertex_index] = i;
        break;
      }
    }
    if(i < n) {
      ++vertex_index;
    }
    else {
      colors[vertex_index] = -1;
      --vertex_index;
    }
  }
  int result = (vertex_index == G->vertex_count);
  return result;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_n_coloring_greedy(const graph *G, int n) {
  int colors[MAX_VERTEX_COUNT];
  int colored_vertices[MAX_VERTEX_COUNT];
  int colored_neighbours_count[MAX_VERTEX_COUNT];
  int i, j;

  int vertex_index = 0;

  for(i = 0; i < G->vertex_count; ++i) {
    colors[i] = -1;
    colored_vertices[i] = -1;
    colored_neighbours_count[i] = 0;
  }

  // chose the vertex with the highest degree as starting vertex
  int max_degree = -1;
  for(i = 0; i < G->vertex_count; ++i) {
    int degree = vertex_degree(G, i);
    if(degree > max_degree) {
      max_degree = degree;
      colored_vertices[vertex_index] = i;
    }
  }

  for(i = 0; i < G->vertex_count; ++i) {
    colored_neighbours_count[i] += is_edge(G, colored_vertices[vertex_index], i);
  }
  colors[colored_vertices[vertex_index]] = 0;

  ++vertex_index;

  while(vertex_index >= 1 && vertex_index < G->vertex_count) {

    if(colored_vertices[vertex_index] == -1) {
      //choose the vertex with the most colored neighbours
      int max_colored_neighbours_count = -1;
      for(i = 0; i < G->vertex_count; ++i) {
        if(colors[i] == -1 && colored_neighbours_count[i] > max_colored_neighbours_count) {
          max_colored_neighbours_count = colored_neighbours_count[i];
          colored_vertices[vertex_index] = i;
        }
      }
      for(i = 0; i < G->vertex_count; ++i) {
        colored_neighbours_count[i] += is_edge(G, colored_vertices[vertex_index], i);
      }
    }

    for(i = colors[colored_vertices[vertex_index]] + 1; i < n; ++i) {
      for(j = 0; j < vertex_index; ++j) {
        if(colors[colored_vertices[j]] == i && is_edge(G, colored_vertices[j], colored_vertices[vertex_index])) {
          break;
        }
      }
      if(j == vertex_index) {
        colors[colored_vertices[vertex_index]] = i;
        break;
      }
    }
    if(i < n) {
      ++vertex_index;
    }
    else {
      for(i = 0; i < G->vertex_count; ++i) {
        colored_neighbours_count[i] -= is_edge(G, colored_vertices[vertex_index], i);
      }
      colors[colored_vertices[vertex_index]] = -1;
      colored_vertices[vertex_index] = -1;
      --vertex_index;
    }
  }
  int result = (vertex_index == G->vertex_count);
  return result;
}

////////////////////////////////////////////////////////////////
// Finds the chromatic number of the graph G.
// WARNING: simple implementation.
////////////////////////////////////////////////////////////////
int chromatic_number(const graph *G) {
  int n;
  for(n = 1; ; ++n) {
    if(find_n_coloring(G, n)) {
      break;
    }
  }
  return n;
}

