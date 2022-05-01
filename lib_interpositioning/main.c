/*
 * Program call malloc and free.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    printf("malloc(%d) = %p\n", sizeof(int), p);
    free(p);
    return 0;
}