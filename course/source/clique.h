////////////////////////////////////////////////////////////////
// @file cliques.h
// @brief Definitions of functions related to cliques and independent sets.
////////////////////////////////////////////////////////////////

#pragma once

int is_Kn(const graph *G, int n, int subset[MAX_VERTEX_COUNT]);

int find_Kn_worker(const graph *G, int n, int subset[MAX_VERTEX_COUNT], int index);

int find_Kn(const graph *G, int n);

int find_Kn_in_subset_worker(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size,
  int indices[MAX_VERTEX_COUNT], int index);

int find_Kn_in_subset(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size);

int clique_number(const graph *G);

int check_edge_adds_kn(const graph *G, int n);

int is_In(const graph *G, int n, int indices[MAX_VERTEX_COUNT]);

int find_In_worker(const graph *G, int n, int indices[MAX_VERTEX_COUNT], int index);

int find_In(const graph *G, int n);

int find_In_in_subset_worker(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size,
  int indices[MAX_VERTEX_COUNT], int index);

int find_In_in_subset(const graph *G, int n,
  int subset[MAX_VERTEX_COUNT], int subset_size);

int independence_number(const graph *G);

int is_max_Kn_free_subset(const graph *G, int n, int subset[MAX_VERTEX_COUNT], int subset_size);
