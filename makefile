all: main 
main: main.o graph.o
	gcc -g -o main main.o graph.o	libfdr.a -lm
main.o:	main.c	
	gcc -g -I/ -c main.c -lm	
graph.o:	graph.c 
	gcc -g -I/ -c graph.c -lm
clean:
	rm -f *.o *~