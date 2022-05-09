#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void* __real_malloc(size_t size);
void __real_free(void* ptr);
void* __real_calloc(size_t nmemb, size_t size);

// malloc wrapper function
void* __wrap_malloc(size_t size) {
    void* ptr = __real_malloc(size);
    if (ptr == NULL) {
        perror("malloc");
        exit(1);
    }
    return ptr;
}

void* __wrap_calloc(size_t nmemb, size_t size) {
    void* ptr = __real_calloc(nmemb, size);
    if (ptr == NULL) {
        perror("calloc");
        exit(1);
    }
    return ptr;
}

// free wrapper function
void __wrap_free(void* ptr) {
    if (!ptr) {
        return;
    }
    __real_free(ptr);
    return;
}