/*
 * Register signal handler in all peer threads other than main.
 * Yet signal handler is run in main thread.
 */
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

void signal_interrupt(int signo) {
    printf("\nhandling SIGINT in thread %ld\n", (unsigned long)pthread_self());
    exit(3);
}

void* block(void* arg) {
    if (signal(SIGINT, signal_interrupt) == SIG_ERR) {
        perror("signal error");
        return NULL;
    }
    printf("register signal handler in thread %ld\n", (unsigned long)pthread_self());
    printf("thread %ld: blocking...\n", (unsigned long)pthread_self());
    pthread_cond_t cond;
    pthread_mutex_t mutext;
    if (pthread_cond_init(&cond, NULL) != 0) {
        perror("pthread_cond_init error");
        exit(1);
    }
    // deadlock
    if (pthread_cond_wait(&cond, &mutext) != 0) {
        perror("pthread_cond_wait error");
        exit(1);
    }
}

int main(void) {
    printf("^C to interrupt\n");

    pthread_t tids[N];

    for (int i = 0; i < N; i++) {
        if (pthread_create(&tids[i], NULL, block, NULL) != 0) {
            perror("pthread_create error\n");
            return 1;
        }
    }

    printf("main thread %ld\n", (unsigned long)pthread_self());
    for (int i = 0; i < N; i++) {
        if (pthread_join(tids[i], NULL) != 0) {
            perror("pthread_join error\n");
            return 1;
        }
    }

    return 0;
}