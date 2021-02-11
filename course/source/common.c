////////////////////////////////////////////////////////////////
// @file common.c
// @brief Implementations of commonly used functions.
////////////////////////////////////////////////////////////////

#include "graph.h"

////////////////////////////////////////////////////////////////
// Finds the number of edges in the graph G.
////////////////////////////////////////////////////////////////
int count_edges(const graph *G) {
  int result = 0;
  int i, j;
  for(i = 1; i < G->vertex_count; ++i) {
    for(j = 0; j < i; ++j) {
      if(is_edge(G, i, j)) {
        ++result;
      }
    }
  }
  return result;
}

////////////////////////////////////////////////////////////////
// Finds the degree of the i-th vertex of the graph G.
////////////////////////////////////////////////////////////////
int vertex_degree(const graph *G, int i) {
  int degree;
  int j;
  degree = 0;
  for(j = 0; j < G->vertex_count; ++j) {
    if(is_edge(G, i, j)) {
      ++degree;
    }
  }
  return degree;
}

////////////////////////////////////////////////////////////////
// Finds the min degree of the graph G.
////////////////////////////////////////////////////////////////
int min_degree(const graph *G) {
  int degree, min_degree;
  int i;
  min_degree = (int)G->vertex_count;
  for(i = 0; i < G->vertex_count; ++i) {
    degree = vertex_degree(G, i);
    if(degree < min_degree) {
      min_degree = degree;
    }
  }
  return min_degree;
}

////////////////////////////////////////////////////////////////
// Finds the max degree of the graph G.
////////////////////////////////////////////////////////////////
int max_degree(const graph *G) {
  int degree, max_degree;
  int i;
  max_degree = 0;
  for(i = 0; i < G->vertex_count; ++i) {
    degree = vertex_degree(G, i);
    if(degree > max_degree) {
      max_degree = degree;
    }
  }
  return max_degree;
}

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////
void add_vertex(graph* G, int neighborhood[MAX_VERTEX_COUNT], int neighborhood_size) {
  int i;
  ++G->vertex_count;
  for(i = 0; i < neighborhood_size; ++i) {
    add_edge(G, (int)G->vertex_count - 1, neighborhood[i]);
  }
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
void remove_vertex(graph *G, int i) {
  graph sub_G;
  memset(&sub_G, 0, sizeof(graph));
  sub_G.vertex_count = G->vertex_count - 1;

  int j, k, l, m;
  for(j = 1; j < G->vertex_count; ++j) {
    if(j == i) continue;
    l = j > i ? j - 1 : j;
    for(k = 0; k < j; ++k) {
      if(k == i) continue;
      m = k > i ? k - 1 : k;
      if(is_edge(G, j, k)) {
        add_edge(&sub_G, l, m);
      }
    }
  }

  *G = sub_G;
}


////////////////////////////////////////////////////////////////
// Constructs the complement of the graph G.
////////////////////////////////////////////////////////////////
void create_complement_graph(const graph* G, graph *G_complement) {
  memset(G_complement, 0, sizeof(graph));
  G_complement->vertex_count = G->vertex_count;
  int i, j;
  for(i = 1; i < G->vertex_count; ++i) {
    for(j = 0; j < i; ++j) {
      if(!is_edge(G, i, j)) {
        add_edge(G_complement, i, j);
      }
    }
  }
}

////////////////////////////////////////////////////////////////
// Counts the number of connected components of the graph G.
////////////////////////////////////////////////////////////////
int count_connected_components(const graph *G) {
  int i, j, k;
  int stack[MAX_VERTEX_COUNT];
  int stack_size = 0;
  int visited[MAX_VERTEX_COUNT];
  int count = 0;
  for (i = 0; i < G->vertex_count; ++i) {
    visited[i] = 0;
  }
  for (i = 0; i < G->vertex_count; ++i) {
    if (!visited[i]) {
      ++count;
      stack[stack_size++] = i;
      visited[i] = count;
      while (stack_size > 0) {
        j = stack[--stack_size];
        for (k = i + 1; k < G->vertex_count; ++k) {
          if (is_edge(G, j, k) && !visited[k]) {
            stack[stack_size++] = k;
            visited[k] = count;
          }
        }
      }
    }
  }
  return count;
}

////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////
int check_sperner(const graph *G) {
  int i, j, k;

  for (i = 0; i < G->vertex_count; ++i) {
    for (j = 0; j < G->vertex_count; ++j) {
      if (i == j) continue;
      for (k = 0; k < G->vertex_count; ++k) {
        if (is_edge(G, i, k) && !is_edge(G, j, k)) {
          break;
        }
      }
      if (k == G->vertex_count) {
        return 1;
      }
    }
  }
  return 0;
}

