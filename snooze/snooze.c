#include <stdio.h>
#include <unistd.h>

#define N 2

int main(void) {
    printf("Slept for %d of %d seconds\n", N - sleep(N), N);
    return 0;
}