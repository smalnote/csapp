#include <stdio.h>
#include <stdlib.h>

#include "filter.h"


extern struct ints handle(struct ints v, int (*f)(int));
extern int gt5(int x);
int is_even(int x);

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct ints v = {a, 10};

    struct ints r = handle(v, gt5);

    int i;
    printf("gt5: ");
    for (i = 0; i < r.size; i++) {
        printf("%d ", r.a[i]);
    }
    printf("\n");

    struct ints rr = handle(r, is_even);

    printf("gt5: is_even: ");
    for (i = 0; i < rr.size; i++) {
        printf("%d ", rr.a[i]);
    }
    printf("\n");

    free(r.a);
    free(rr.a);
    return 0;
}