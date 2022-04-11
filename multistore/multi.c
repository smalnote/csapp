// generate assembly code, AT&T instruction set by default
// gcc -Og -S multi.c
// intel instruction set
// gcc -Og -S -masm=intel multi.c
long multi2(long, long);
void multistore(long x, long y, long *dest) {
    long t = multi2(x, y);
    *dest = t;
}