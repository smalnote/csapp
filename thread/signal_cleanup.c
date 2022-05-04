/*
 * Run two thread simultaneously, main trhead handle SIGQUIT signal and
 * do a cleanup and terminate child thread and exit.
 */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#define N 1

int _exit_indicator = 0;

void signal_interrupt(int signo) {
    printf("\nhandling SIGINT in thread %ld\n", (unsigned long)pthread_self());
    _exit_indicator = 1;
}

void* worker(void* arg) {
    int* _exit_p = (int*)arg;
    int count = 0;
    while (!*_exit_p) {
        printf("worker thread %ld: %05d...\n", (unsigned long)pthread_self(), count++);
        sleep(1);
    }
    printf("cleaning up... \n");
    sleep(3);
    printf("done\n");
    return NULL;
}

int main(void) {
    if (signal(SIGINT, signal_interrupt) == SIG_ERR) {
        perror("signal error");
        return 1;
    }
    printf("main thread %ld\n", (unsigned long)pthread_self());
    printf("^C to interrupt\n");
    pthread_t tid;
    if (pthread_create(&tid, NULL, worker, &_exit_indicator) != 0) {
        printf("pthread_create error\n");
        return 1;
    }

    if (pthread_join(tid, NULL) != 0) {
        printf("pthread_join error\n");
        return 1;
    }

    return 0;
}