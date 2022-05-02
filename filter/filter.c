#include "filter.h"

#include <stdlib.h>

ints handle(struct ints v, filter f) {
    int* ra = malloc(sizeof(int) * v.size);
    int i = 0, j;
    for (j = 0; j < v.size; j++) {
        if (f(v.a[j])) {
            ra[i++] = v.a[j];
        }
    }
    ints result = {ra, i};
    return result;
}

int gt5(int x) { return x > 5; }

int is_even(int x) { return x % 2 == 0; }

int is_odd(int x) { return x & 1 == 1; }