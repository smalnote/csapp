/*
 * I/O multiplexing concurrency.
 */

#include <stdio.h>
#include <sys/select.h>

int main(void) {
    fd_set read_set;
    FD_ZERO(&read_set);
    printf("sizeof(fd_set) = %ld\n", sizeof(read_set));
    return 0;
}