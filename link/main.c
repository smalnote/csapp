#include <stdio.h>

int buf[2] = {1, 2};
int *p, *q; // p will be ignore likely
extern void swap();

int a(){
}

int main() {
    q = buf;
    printf("%d %d\n", q[0], *(q+1));
    swap();
    printf("%d %d\n", buf[0], buf[1]);
    return 0;
}