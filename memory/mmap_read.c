/*
 * Use map mapping to read a file
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char s[100];
    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(0);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf(s, "open file '%s' failed", argv[1]);
        perror(s);
        exit(1);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        printf(s, "fstat file '%s' failed", argv[1]);
        perror(s);
        exit(1);
    }

    if (st.st_size == 0) {
        printf("file '%s' is empty\n", argv[1]);
        exit(1);
    }

    void* bufp = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (bufp == NULL) {
        sprintf(s, "mmap file '%s' failed", argv[1]);
        perror(s);
        exit(1);
    }

    write(STDOUT_FILENO, bufp, st.st_size);
    printf("\n");

    if (munmap(bufp, st.st_size) == -1) {
        sprintf(s, "munmap buffer '%#x'(%d) failed", bufp, sizeof(bufp));
        perror(s);
        exit(1);
    }

    return 0;
}