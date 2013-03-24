all: clean test
	gcc main.c -o main graph.o graph_search.o vertex.o

clean:
	rm -f *_test
	rm -f *.o
	rm -f main

graph:
	gcc -g -c graph.c

graph_search:
	gcc -g -c graph_search.c

graph_search_test: vertex graph graph_search
	gcc -g graph_search_test.c -o graph_search_test graph.o graph_search.o vertex.o

graph_test: graph vertex
	gcc -g graph_test.c -o graph_test graph.o vertex.o

test: test_vertex test_graph test_graph_search

test_graph: graph_test
	./graph_test

test_graph_search: graph_search_test
	./graph_search_test

test_vertex: vertex_test
	./vertex_test

vertex:
	gcc -g -c vertex.c

vertex_test: vertex
	gcc -g vertex_test.c -o vertex_test vertex.o

.PHONY: test
