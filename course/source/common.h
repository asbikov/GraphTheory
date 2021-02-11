////////////////////////////////////////////////////////////////
// @file common.h
// @brief Definitions of commonly used functions.
////////////////////////////////////////////////////////////////

#pragma once

int count_edges(const graph *G);

int vertex_degree(const graph *G, int i);

int min_degree(const graph *G);

int max_degree(const graph *G);

void add_vertex(graph* G, int neighborhood[MAX_VERTEX_COUNT], int neighborhood_size);

void remove_vertex(graph *G, int i);

void create_complement_graph(const graph* G, graph *G_complement);

int count_connected_components(const graph* G);

int check_sperner(const graph* G);
