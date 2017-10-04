#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

Queue* new_Queue() {
    Queue* opt = malloc(sizeof(Queue));
    if (opt == NULL) {
        puts("Fatal error! Out of memory!");
        return NULL;
    }
    opt->head = NULL;
    opt->tail = NULL;
    opt->cnt = 0;
    return opt;
}

int enqueue(Queue* q, Car* c) {
    if (q == NULL) {
        return 1;
    }
    if (q->cnt == 0) {
        q->head = c;
        q->tail = c;
    } else {
        q->tail->next = c;
        q->tail = c;
    }
    q->cnt++;
    return 1;
}

Car* dequeue(Queue* q) {
    if (q == NULL || q->cnt == 0) {
        return NULL;
    }
    Car* c = q->head;
    q->head = q->head->next;
    q->cnt--;
    return c;
}

int free_Queue(Queue* q) {
    if (q == NULL) {
        return 1;
    }
    if (q->cnt != 0) {
        for (int i = 0; i < q->cnt; i++) {
            Car* c = q->head;
            q->head = q->head->next;
            free(q->head);
        }
    }
    free(q);
    return 0;
}
