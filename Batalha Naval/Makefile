all: buscabinaria.o principal.o
	@gcc -o exe buscabinaria.o principal.o

buscabinaria.o: buscabinaria.c
	@gcc buscabinaria.c -c -lm -Wall

principal.o: principal.c
	@gcc principal.c -c -lm -Wall

exe:
	@./exe