/*
 * Simple multi-threaded echo server using multiplexing I/O.
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "listen.h"
#include "rio.h"
#include "sbuf.h"

#define NTHREADS 4
#define SBUFSIZE 32
/* Misc constants */
#define MAXLINE 8192 /* Max text line length */
#define MAXBUF 8192  /* Max I/O buffer size */

sbuf_t sbuf;
void *thread(void *vargp);

static int byte_cnt;
static sem_t mutex;
static void init_echo_cnt(void) {
    sem_init(&mutex, 0, 1);
    byte_cnt = 0;
}
void echo_cnt(int connfd);

int __wrap_open_listenfd(char *port) {
    int rc;
    if ((rc = open_listenfd(port)) < 0) {
        perror("open_listenfd error");
        exit(1);
    }
    return rc;
}

int main(int argc, char *argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 0;
    }
    listenfd = __wrap_open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);
    for (int i = 0; i < NTHREADS; i++) {
        pthread_create(&tid, NULL, thread, NULL);
    }

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }

    return 0;
}

void *thread(void *vargp) {
    pthread_detach(pthread_self());
    while (1) {
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        close(connfd);
    }
}

void echo_cnt(int connfd) {
    int n;
    char buf[MAXLINE];
    rio_t rio;
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, init_echo_cnt);
    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        sem_wait(&mutex);
        byte_cnt += n;
        printf("server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
        sem_post(&mutex);
        rio_writen(connfd, buf, n);
    }
}