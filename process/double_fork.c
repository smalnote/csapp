/*
 * Double fork creates a truly daemonized process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid, ppid, pgid, sid;
    pid = fork();
    if (pid == -1) {
        perror("fork failed ");
        return -1;
    } else if (pid == 0) {
        pid = getpid();
        ppid = getppid();
        pgid = getpgrp();
        sid = getsid(0);
        printf("child       , pid: %d, ppid: %d, pgid: %d, sid: %d\n", pid, ppid, pgid, sid);

        setsid();

        pid = getpid();
        ppid = getppid();
        pgid = getpgrp();
        sid = getsid(0);
        printf("child setsid, pid: %d, ppid: %d, pgid: %d, sid: %d\n", pid, ppid, pgid, sid);

        pid = fork();
        if (pid == -1) {
            perror("fork failed ");
            return -1;
        } else if (pid == 0) {
            pid = getpid();
            ppid = getppid();
            pgid = getpgrp();
            sid = getsid(0);
            printf("grandchild, pid: %d, ppid: %d, pgid: %d, sid: %d\n", pid, ppid, pgid, sid);
            printf("grandchild, in new pgid but pid != pgid, truly daemonized\n");
            return 0;
        }

        return 0;
    }
    return 0;
}