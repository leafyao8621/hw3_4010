#include "Queue.h"
#include "../engine/api.h"

typedef struct Bridge {
    int stat;
    Queue* north_queue;
    Queue* south_queue;
    double time;
    Queue* enroute;
    int is_grouped;
    Engine* engine;
} Bridge;

Bridge* new_Bridge();
int arrive(Bridge* b, int dir);
int move(Bridge* b, int dir);
int depart(Bridge* b);
double gen_time();
double gen_delay();
int free_Bridge(Bridge* b);
