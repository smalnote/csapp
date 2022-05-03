// #1 line
// #2 line
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 11  // number of byte in first two lines of this file
int close_c(int fd);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char buf[N + 1];
    buf[N] = '\0';
    pid_t pid;

    int fd = open(argv[1], O_RDONLY);
    if ((pid = fork()) == 0) {
        printf("child process #%d read %d bytes with fd %d\n", getpid(), N, fd);
        read(fd, buf, N);
        printf("%s", buf);
        return 0;
    }
    wait(NULL);
    printf("parent process #%d read %d bytes with fd %d\n", getpid(), N, fd);
    read(fd, buf, N);
    printf("%s", buf);

    close_c(fd);
    return 0;
}

// close file descriptor fd and check error
int close_c(int fd) {
    if (close(fd) == -1) {
        perror("close");
        exit(-1);
    }
}
