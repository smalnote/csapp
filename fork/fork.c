#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int x = 1;
    if (Fork() == 0) {
        printf("p1: x = %d\n", ++x);
    }
    printf("p2: x = %d\n", --x);
    return 0;
}

pid_t Fork() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    }
    return pid;
}