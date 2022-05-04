/*
 * Use process to handle multiple clients.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

void echo(int connfd);
void signal_handler(int sig);
void signal_t(int sig, __sighandler_t handler);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    signal_t(SIGCHLD, signal_handler);

    // create a TCP socket descriptor
    // listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)

    // bind socket descriptor to address
    // bind(listenfd, p->ai_addr, p->ai_addrlen)

    // Make it a listening socket ready to accept connection requests
    // listen(listenfd, LISTENQ)

    // infinit loop

    // accept client connect
    // connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen)

    // fork a child process handle connfd
    // {
    // close(listenfd) copied from parent
    // read from connfd and write to connfd
    // close(connfd) copied from parent
    // }

    // close(connfd) in parent process since it's handled in child

    return 0;
}

void signal_t(int sig, __sighandler_t handler) {
    if (signal(sig, handler) == SIG_ERR) {
        perror("signal");
        exit(-1);
    }
}

void signal_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
    return;
}