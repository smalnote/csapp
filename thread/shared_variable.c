/*
 * Multiple thread increase shared variable
 */
#include <pthread.h>
#include <stdio.h>

#define N 10

void* increase(void* arg) {
    int i;
    int* val = (int*)arg;
    for (i = 0; i < 1000000; i++) {
        *val += 1;
    }
    printf("BOOM! thread %ld: %d\n", (unsigned long)pthread_self(), *val);
    return NULL;
}

int main(void) {
    int cnt = 0;

    int i;
    pthread_t tid[N];
    for (i = 0; i < N; i++) {
        if (pthread_create(tid + i, NULL, increase, &cnt) != 0) {
            printf("pthread_create error\n");
            return 1;
        }
    }

    for (i = 0; i < N; i++) {
        if (pthread_join(tid[i], NULL) != 0) {
            printf("pthread_join error\n");
            return 1;
        }
    }

    printf("BOOM! cnt = %d\n", cnt);

    return 0;
}