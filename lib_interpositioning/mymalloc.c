#ifdef RUNTIME
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/* malloc wrapper function */
void* malloc(size_t size) {
    void* (*real_malloc)(size_t);
    char* error;
    // Get address of libc malloc
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    char* ptr = real_malloc(size);
    printf("interpositioned malloc(%d) = %p\n", size, ptr);
    return ptr;
}

void free(void* ptr) {
    if (!ptr) {
        return;
    }

    void (*real_free)(void*);
    char* error;
    // Get address of libc free
    real_free = dlsym(RTLD_NEXT, "free");
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    real_free(ptr);
    printf("interpositioned free(%p)\n", ptr);
}

#endif

#ifdef LINKTIME

#include <stdio.h>

void* __real_malloc(size_t size);
void __real_free(void* ptr);

// malloc wrapper function
void* __wrap_malloc(size_t size) {
    void* ptr = __real_malloc(size);
    printf("interpositioned malloc(%d) = %p\n", size, ptr);
    return ptr;
}

// free wrapper function
void __wrap_free(void* ptr) {
    if (!ptr) {
        return;
    }

    __real_free(ptr);
    printf("interpositioned free(%p)\n", ptr);
}

#endif