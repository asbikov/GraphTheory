////////////////////////////////////////////////////////////////
// @file io.h
// @brief Definitions of functions related to I/O.
////////////////////////////////////////////////////////////////

#pragma once


int read_graph_file(graph *G, FILE *file);

void write_graph_file(const graph *G, FILE *file);

int read_graph(graph *G);

void write_graph(const graph *G);
