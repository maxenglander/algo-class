CFLAGS += -g
.PHONY: test_all

all: main

clean:
	rm -f *.o *_test main

edge.o:

edge_test: edge.o iterator.o list.o node.o vertex.o

graph_search.o:

graph_search_test: edge.o graph.o graph_search.o iterator.o list.o node.o vertex.o

graph.o:

graph_test: edge.o graph.o iterator.o list.o node.o vertex.o

iterator.o:

iterator_test: iterator.o list.o node.o

list.o:

list_test: iterator.o list.o node.o

main: edge.o graph.o graph_search.o iterator.o list.o node.o vertex.o

node.o:

node_test: node.o

test_all: test_node test_list test_iterator test_vertex test_edge test_graph  
	
test_edge: edge_test
	./edge_test

test_graph: graph_test
	./graph_test

test_graph_search: graph_search_test
	./graph_search_test

test_iterator: iterator_test
	./iterator_test

test_list: list_test
	./list_test

test_node: node_test
	./node_test

test_vertex: vertex_test
	./vertex_test

vertex.o:

vertex_test: edge.o iterator.o list.o node.o vertex.o

