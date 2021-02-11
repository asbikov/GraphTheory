////////////////////////////////////////////////////////////////
// @file cliques.c
// @brief Implementations of functions related to cliques and independent sets.
////////////////////////////////////////////////////////////////

#include "graph.h"

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_Kn(const graph *G, int n, int subset[MAX_VERTEX_COUNT]) {
  int i, j;
  for(i = 1; i < n; ++i) {
    for(j = 0; j < i; ++j) {
      if(!is_edge(G, subset[i], subset[j])) {
        return 0;
      }
    }
  }
  return 1;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_Kn_worker(const graph *G, int n, int vertices[MAX_VERTEX_COUNT], int index) {
  int i, j;
  if(index == n) {
    return 1;
  }
  int next_index = (index == 0) ? 0 : vertices[index - 1] + 1;
  for(i = next_index; i < G->vertex_count - n + index + 1; ++i) {
    int can_add_vertex = 1;
    for(j = 0; j < index && can_add_vertex; ++j) {
      if(!is_edge(G, i, vertices[j])) {
        can_add_vertex = 0;
      }
    }
    if(can_add_vertex) {
      vertices[index] = i;
      if(find_Kn_worker(G, n, vertices, index + 1)) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_Kn(const graph *G, int n) {
  int vertices[MAX_VERTEX_COUNT];
  return find_Kn_worker(G, n, vertices, 0);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_Kn_in_subset_worker(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size,
  int vertices[MAX_VERTEX_COUNT], int index) {
  int i, j;
  if(index == n) {
    return 1;
  }
  int next_index = (index == 0) ? 0 : vertices[index - 1] + 1;
  for(i = next_index; i < subset_size - n + index + 1; ++i) {
    int can_add_vertex = 1;
    for(j = 0; j < index && can_add_vertex; ++j) {
      if(!is_edge(G, subset[i], subset[vertices[j]])) {
        can_add_vertex = 0;
      }
    }
    if(can_add_vertex) {
      vertices[index] = i;
      if(find_Kn_in_subset_worker(G, n, subset, subset_size, vertices, index + 1)) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_Kn_in_subset(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size) {
  int vertices[MAX_VERTEX_COUNT];
  return find_Kn_in_subset_worker(G, n, subset, subset_size, vertices, 0);
}

////////////////////////////////////////////////////////////////
// Finds the clique number of the graph G.
// WARNING: simple implementation.
////////////////////////////////////////////////////////////////
int clique_number(const graph *G) {
  int result;
  for(result = 1; result <= G->vertex_count; ++result) {
    if(!find_Kn(G, result)) {
      break;
    }
  }
  return result-1;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int check_edge_adds_kn(const graph *G, int n) {
  if(n <= 2) {
    return 1;
  }
  graph G_copy = *G;
  int i, j;
  for(i = 1; i < G_copy.vertex_count; ++i) {
    for(j = 0; j < i; ++j) {
      if(!is_edge(&G_copy, i, j)) {
        add_edge(&G_copy, i, j);
        int neighboor_indices[MAX_VERTEX_COUNT];
        int neighboor_indices_count = 0;
        int k;
        for(k = 0; k < G_copy.vertex_count; ++k) {
          if(k != i && k != j && is_edge(&G_copy, k, i) && is_edge(&G_copy, k, j)) {
            neighboor_indices[neighboor_indices_count++] = k;
          }
        }
        if(!find_Kn_in_subset(&G_copy, n - 2, neighboor_indices, neighboor_indices_count)) {
          return 0;
        }
        remove_edge(&G_copy, i, j);
      }
    }
  }
  return 1;
}


////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_In(const graph *G, int n, int vertices[MAX_VERTEX_COUNT]) {
  int i, j;
  for(i = 1; i < n; ++i) {
    for(j = 0; j < i; ++j) {
      if(is_edge(G, vertices[i], vertices[j])) {
        return 0;
      }
    }
  }
  return 1;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_In_worker(const graph *G, int n, int vertices[MAX_VERTEX_COUNT], int index) {
  int i, j;
  if(index == n) {
    return 1;
  }
  int next_index = (index == 0) ? 0 : vertices[index - 1] + 1;
  for(i = next_index; i < G->vertex_count - n + index + 1; ++i) {
    int can_add_vertex = 1;
    for(j = 0; j < index && can_add_vertex; ++j) {
      if(is_edge(G, i, vertices[j])) {
        can_add_vertex = 0;
      }
    }
    if(can_add_vertex) {
      vertices[index] = i;
      if(find_In_worker(G, n, vertices, index + 1)) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_In(const graph *G, int n) {
  int vertices[MAX_VERTEX_COUNT];
  return find_In_worker(G, n, vertices, 0);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_In_in_subset_worker(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size,
  int vertices[MAX_VERTEX_COUNT], int index) {
  int i, j;
  if(index == n) {
    return 1;
  }
  int next_index = (index == 0) ? 0 : vertices[index - 1] + 1;
  for(i = next_index; i < subset_size - n + index + 1; ++i) {
    int can_add_vertex = 1;
    for(j = 0; j < index && can_add_vertex; ++j) {
      if(is_edge(G, subset[vertices[j]], subset[i])) {
        can_add_vertex = 0;
      }
    }
    if(can_add_vertex) {
      vertices[index] = i;
      if(find_In_in_subset_worker(G, n, subset, subset_size, vertices, index + 1)) {
        return 1;
      }
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int find_In_in_subset(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size) {
  int vertices[MAX_VERTEX_COUNT];
  return find_In_in_subset_worker(G, n, subset, subset_size, vertices, 0);
}

////////////////////////////////////////////////////////////////
// Finds the independent set number of the graph G.
// WARNING: simple implementation.
////////////////////////////////////////////////////////////////
int independence_number(const graph *G) {
  int result;
  for(result = 1; result <= G->vertex_count; ++result) {
    if(!find_In(G, result)) {
      break;
    }
  }
  return result - 1;
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////
int is_max_Kn_free_subset(const graph *G, int n, int subset[MAX_VERTEX_COUNT], int subset_size) {
  if(find_Kn_in_subset(G, n, subset, subset_size)) {
    return 0;
  }
  int i, j;
  int complement_subset[MAX_VERTEX_COUNT];
  int complement_subset_size = 0;
  j = 0;
  for(i = 0; i < G->vertex_count; ++i) {
    if(subset[j] == i) {
      ++j;
    }
    else {
      complement_subset[complement_subset_size++] = i;
    }
  }
  for(i = 0; i < complement_subset_size; ++i) {
    subset[subset_size] = complement_subset[i];
    if(!find_Kn_in_subset(G, n, subset, subset_size + 1)) {
      return 0;
    }
  }
  return 1;
}
