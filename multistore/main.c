#include <stdio.h>

// generate executable
// gcc -Og -o multistore main.c multi.c
void multistore(long, long, long *);

int main() {
    long d;
    multistore(2, 3, &d);
    printf("2 * 3 --> %ld\n", d);
    return 0;
}

int multi2(long x, long y) {
    return x * y;
}