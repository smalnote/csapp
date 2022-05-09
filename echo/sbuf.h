#ifndef SBUF_H
#define SBUF_H
#include <semaphore.h>

typedef struct {
    int *buf;    /* Buffer array */
    int n;       /* Maximnum number of slots */
    int front;   /* buf[(front+1)%n] is the first item */
    int rear;    /* buf[rear%n] is the last item */
    sem_t mutex; /* Protects access to buf */
    sem_t slots; /* Counts available slots */
    sem_t items; /* Counts available items */
} sbuf_t;

/* Create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n);

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp);

void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);

#endif