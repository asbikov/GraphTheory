source_dir=./
output_dir=./

CFLAGS=-O2
LDFLAGS=-lm

graph=\
	$(source_dir)/impl.o\
	$(source_dir)/common.o\
	$(source_dir)/clique.o\
	$(source_dir)/coloring.o\
	$(source_dir)/io.o\
	

executables=\
	$(output_dir)/create_n_vertex_graph\
	$(output_dir)/add_edge\
	$(output_dir)/add_edge_i_j\
	$(output_dir)/remove_edge\
	$(output_dir)/remove_edge_i_j\
	$(output_dir)/complement\
	$(output_dir)/kn\
	$(output_dir)/cn\
	$(output_dir)/is_triangle_free\
	$(output_dir)/filter\
	$(output_dir)/add_vertex\
	$(output_dir)/add_isolated_vertex\
	$(output_dir)/remove_vertex\
	$(output_dir)/add_vertex_ramsey_p_q\
	$(output_dir)/divide\
	$(output_dir)/divide_by\
	$(output_dir)/extend\
	$(output_dir)/is_vertex_critical_chromatic\
	$(output_dir)/is_edge_critical_chromatic\
	$(output_dir)/fv33\
	$(output_dir)/fvpq\
	$(output_dir)/fv\
	$(output_dir)/fv_critical\
	$(output_dir)/fe33\
	$(output_dir)/fe33_critical\
	$(output_dir)/2dot\
	

all: $(executables)

$(output_dir)/create_n_vertex_graph: $(graph) $(source_dir)/main_create_n_vertex_graph.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/add_edge: $(graph) $(source_dir)/main_add_edge.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/add_edge_i_j: $(graph) $(source_dir)/main_add_edge_i_j.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/remove_edge: $(graph) $(source_dir)/main_remove_edge.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/remove_edge_i_j: $(graph) $(source_dir)/main_remove_edge_i_j.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/complement: $(graph) $(source_dir)/main_complement.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/kn: $(graph) $(source_dir)/main_kn.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/cn: $(graph) $(source_dir)/main_cn.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/is_triangle_free: $(graph) $(source_dir)/main_is_triangle_free.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/filter: $(graph) $(source_dir)/main_filter.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/is_maximal: $(graph) $(source_dir)/main_is_maximal.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/add_vertex: $(graph) $(source_dir)/main_add_vertex.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/add_isolated_vertex: $(graph) $(source_dir)/main_add_isolated_vertex.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/remove_vertex: $(graph) $(source_dir)/main_remove_vertex.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/add_vertex_ramsey_p_q: $(graph) $(source_dir)/main_add_vertex_ramsey_p_q.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/divide: $(graph) $(source_dir)/main_divide.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/divide_by: $(graph) $(source_dir)/main_divide_by.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/extend: $(graph) $(source_dir)/main_extend.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/is_vertex_critical_chromatic: $(graph) $(source_dir)/main_is_vertex_critical_chromatic.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/is_edge_critical_chromatic: $(graph) $(source_dir)/main_is_edge_critical_chromatic.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fv33: $(graph) $(source_dir)/main_fv33.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fvpq: $(graph) $(source_dir)/main_fvpq.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fv: $(graph) $(source_dir)/main_fv.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fv_critical: $(graph) $(source_dir)/main_fv_critical.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fe33: $(graph) $(source_dir)/main_fe33.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/fe33_critical: $(graph) $(source_dir)/main_fe33_critical.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(output_dir)/2dot: $(graph) $(source_dir)/main_2dot.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


clean:
	rm -f $(source_dir)/*.o
