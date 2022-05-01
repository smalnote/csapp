/*
 * This program forks a child process,
 * both the parent and child process print its pid, ppid, and sid,
 * check what different whether parent wait child or not.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid, ppid, pgid, sid;

    pid = getpid();
    ppid = getppid();
    pgid = getpgrp();
    sid = getsid(0);
    printf("parent pid: %d, ppid: %d, pgid: %d, sid: %d\n", pid, ppid, pgid, sid);

    pid = fork();
    if (pid == -1) {
        perror("fork failed ");
        return -1;
    } else if (pid == 0) {
        pid = getpid();
        ppid = getppid();
        pgid = getpgrp();
        sid = getsid(0);
        printf("child  pid: %d, ppid: %d, pgid: %d, sid: %d\n", pid, ppid, pgid, sid);
        return 0;
    }
    return 0;
}