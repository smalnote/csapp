/*
 * Multiple thread increase shared variable with semaphore.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct {
    sem_t mutex;
    volatile int val;
} mutexval_t;

void* increase(void* arg) {
    mutexval_t* v = (mutexval_t*)arg;

    if (sem_wait(&(v->mutex)) != 0) {
        perror("sem_wait error");
        exit(3);  // terminate all threads
    }

    int i;
    for (i = 0; i < 1000000; i++) {
        v->val += 1;
    }

    printf("thread %ld: %d\n", (unsigned long)pthread_self(), v->val);
    if (sem_post(&(v->mutex)) != 0) {
        perror("sem_post error");
        exit(3);
    }
    return NULL;
}

int main(void) {
    mutexval_t v = {
        .val = 0,
    };
    if (sem_init(&(v.mutex), 0, 1) != 0) {
        perror("sem_init error");
        return 1;
    }

    int i;
    pthread_t tid[N];
    for (i = 0; i < N; i++) {
        if (pthread_create(tid + i, NULL, increase, &v) != 0) {
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

    printf("val = %d\n", v.val);

    return 0;
}