.PHONY: *
main: 
	gcc -Og -c main.c
swap:
	gcc -Og -c swap.c
prog: main swap
	gcc -Og -fno-common -o prog main.o swap.o && ./prog

prog2:
	gcc -Og -o prog2 main.c swap.c && ./prog2