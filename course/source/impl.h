////////////////////////////////////////////////////////////////
// @file impl.h
// @brief Definitions related to the graph structure.
////////////////////////////////////////////////////////////////

#pragma once

#define MAX_VERTEX_COUNT  64

#define MAX_EDGES_COUNT   (MAX_VERTEX_COUNT*(MAX_VERTEX_COUNT-1)/2)

typedef struct {
  int64_t vertex_count;
  uint64_t adjacency[MAX_VERTEX_COUNT];
} graph;

void add_edge(graph* G, int i, int j);
void remove_edge(graph* G, int i, int j);
int is_edge(const graph* G, int i, int j);

