////////////////////////////////////////////////////////////////
// @file io.c
// @brief Implementations of functions related to I/O.
////////////////////////////////////////////////////////////////

#include "graph.h"

////////////////////////////////////////////////////////////////
// Reads a graph G from a file in graph6 format.
////////////////////////////////////////////////////////////////
int read_graph_file(graph *G, FILE *file) {
  int i, j, k;
  char char_buffer[MAX_EDGES_COUNT / 6 + 16];
  int offset;
  int bits_count;

  memset(G, 0, sizeof(graph)); 
  
  int result = fgets(char_buffer, MAX_EDGES_COUNT / 6 + 16, file) != NULL;
  if(result) {
    offset = strlen(char_buffer) - 1;
    for(i = 0; i < offset; ++i) {
      char_buffer[i] -= 63;
    }

    if(char_buffer[0] != 63) {
      bits_count = 6;
      offset = 0;
    }
    else if(char_buffer[1] != 63) {
      bits_count = 18;
      offset = 1;
    }
    else {
      bits_count = 36;
      offset = 2;
    }
    for(i = 0; i < bits_count; ++i) {
      j = offset + (bits_count - 1 - i) / 6;
      k = i % 6;
      G->vertex_count |= (char_buffer[j] & (1 << k)) ? (1 << i) : 0;
    }
    offset += bits_count / 6;

    bits_count = (int)(G->vertex_count * (G->vertex_count - 1) / 2);
    i = 0;
    for(j = 1; j < G->vertex_count; ++j) {
      for(k = 0; k < j; ++k) {
        if(char_buffer[offset + i / 6] & (1 << (6 - 1 - i % 6))) {
          add_edge(G, j, k);
        }
        ++i;
      }
    }
  }
  return result;
}

////////////////////////////////////////////////////////////////
// Writes a graph G to a file in graph6 format.
////////////////////////////////////////////////////////////////
void write_graph_file(const graph *G, FILE *file) {
  int i, j, k;
  char char_buffer[MAX_EDGES_COUNT / 6 + 16];
  int offset;
  int bits_count;
  
  bits_count = (int)(G->vertex_count * (G->vertex_count - 1) / 2);
  memset(char_buffer, 0, bits_count / 6 + 16);
  
  if(G->vertex_count > 258047) {
    char_buffer[0] = 63;
    char_buffer[1] = 63;
    offset = 2;
    bits_count = 36;
  }
  else if(G->vertex_count > 62) {
    char_buffer[0] = 63;
    offset = 1;
    bits_count = 18;
  }
  else {
    offset = 0;
    bits_count = 6;
  }
  for(i = 0; i < bits_count; ++i) {
    j = offset + (bits_count - 1 - i) / 6;
    k = i % 6;
    char_buffer[j] |= ((int)G->vertex_count & (1 << i)) ? (1 << k) : 0;
  }
  offset += bits_count / 6;

  bits_count = (int)(G->vertex_count * (G->vertex_count - 1) / 2);
  i = 0;
  for(j = 1; j < G->vertex_count; ++j) {
    for(k = 0; k < j; ++k) {
      char_buffer[offset + i / 6] |= is_edge(G, j, k) ? (1 << (6 - 1 - i % 6)) : 0;
      ++i;
    }
  }
  offset += bits_count ? ((bits_count - 1) / 6 + 1) : 0;
  
  for(i = 0; i < offset; ++i) {
    char_buffer[i] += 63;
  }
  char_buffer[offset] = '\0';
  fprintf(file, "%s\n", char_buffer);
}

////////////////////////////////////////////////////////////////
// Reads a graph G from stdin.
////////////////////////////////////////////////////////////////
int read_graph(graph *G) {
  return read_graph_file(G, stdin);
}

////////////////////////////////////////////////////////////////
// Writes a graph G to stdout.
////////////////////////////////////////////////////////////////
void write_graph(const graph *G) {
  write_graph_file(G, stdout);
}
