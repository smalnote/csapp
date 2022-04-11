.PHONY: *

# $@ is the target
# $^ is the source
# gcc -c -o $@ $< 
compile:
	gcc -c addvec.c multvec.c
archive: compile
	ar rcs libvector.a addvec.o multvec.o
main: 
	gcc -c main.c


prog: main archive
	gcc -static -o prog main.o ./libvector.a

prog2: main archive
	gcc -static -o prog main.o -L. -lvector