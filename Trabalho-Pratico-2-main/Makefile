all: principal.o matriz.o
	@gcc principal.o matriz.o -o exe
lista.o: matriz.c
	@gcc matriz.c -c -lm -Wall
pratica.o: pratica.c
	@gcc principal.c -c -lm -Wall
run:
	@./exe
