/*
 * Create a new thread and wait for it to finish.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* job(void* argv) {
    pthread_t tid = pthread_self();
    printf("Hello from thread %lu\n", (unsigned long)tid);
    sleep(10);
    return 0;
}

int main(void) {
    pthread_t tid;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);

    if (pthread_create(&tid, &tattr, job, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_join(tid, NULL) != 0) {
        perror("pthread_join");
        return 1;
    };
    printf("Thread %lu joined\n", (unsigned long)tid);
    return 0;
}