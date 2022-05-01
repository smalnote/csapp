myalloc.so:
	gcc -DRUNTIME -shared -fPIC -o libmymalloc.so mymalloc.c -ldl
run_prog: clean prog myalloc.so
	gcc -o prog main.c && LD_PRELOAD="./libmymalloc.so" ./prog

mymalloc.o:
	gcc -DLINKTIME -c mymalloc.c
prog.o:
	gcc -c -o prog.o main.c
link_run_prog: clean mymalloc.o prog.o
	gcc -Wl,--wrap,malloc -Wl,--wrap,free -o prog prog.o mymalloc.o && ./prog

clean:
	rm -f prog *.o *.so

