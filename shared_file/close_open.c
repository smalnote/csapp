#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd1, fd2;

    fd1 = open("./makefile", O_RDONLY, 0);
    fd2 = open("./close_open.c", O_RDONLY, 0);
    close(fd2);
    fd2 = open("./close_open.c", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);

    return 0;
}