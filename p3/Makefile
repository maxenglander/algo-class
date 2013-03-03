all: clean edge vertex graph
	gcc -g -o main main.c edge.o vertex.o graph.o

clean:
	rm -f *.o main

edge:
	gcc -g -c edge.c

graph:
	gcc -g -c graph.c

vertex:
	gcc -g -c vertex.c
