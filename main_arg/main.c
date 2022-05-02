#include <stdio.h>
#include <unistd.h>

void print_strings(char* name, char* strings[]);

int main(int argc, char* argv[], char* envp[]) {
    printf("argc:\n\t%d\n", argc);
    print_strings("argv", argv);
    print_strings("envp", envp);
    return 0;
}

void print_strings(char* name, char* strings[]) {
    printf("%s:\n", name);
    int i;
    for (i = 0; strings[i] != NULL; i++) {
        printf("\t%s[%d]: %s\n", name, i, strings[i]);
    }
}