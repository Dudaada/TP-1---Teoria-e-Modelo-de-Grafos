all:
	gcc -o programa src/main.c src/grafo.c
	./programa inputs/exemplo.txt
