typedef struct ints {
    int* a;
    int size;
} ints;

typedef int (*filter)(int);

ints handle(struct ints v, filter f);
int gt5(int x);
int is_even(int x);
int is_odd(int x);