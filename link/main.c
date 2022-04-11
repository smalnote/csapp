#include <stdio.h>

int buf[2] = {1, 2};
int *p, *q;
extern void swap();

int main() {
    q = buf;
    printf("%d %d\n", q[0], *(q+1));
    swap();
    printf("%d %d\n", buf[0], buf[1]);
    return 0;
}