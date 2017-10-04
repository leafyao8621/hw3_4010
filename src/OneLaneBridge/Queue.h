#include "Car.h"

typedef struct Queue {
    Car* head;
    Car* tail;
    int cnt;
} Queue;

Queue* new_Queue();
int enqueue(Queue* q, Car* c);
Car* dequeue(Queue* q);
int free_Queue(Queue* q);
