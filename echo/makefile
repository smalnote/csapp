.PHONY: *



wrapper:
	gcc -o wrapper.o -c wrapper.c

sbuf:
	gcc -o sbuf.o -c sbuf.c

rio:
	gcc -o rio.o -c rio.c

listen:
	gcc -o listen.o -c listen.c

echo:
	gcc -std=gnu99 -o echo.o -c echo.c

prog: wrapper echo sbuf listen
	./build.sh listen.o wrapper.o sbuf.o rio.o echo.o

run: prog
	./prog 10089