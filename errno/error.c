#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    perror("message passed to perror");
    printf("%s\n", strerror(errno));
    return 0;
}