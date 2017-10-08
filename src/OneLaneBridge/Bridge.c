#include <stdio.h>
#include <stdlib.h>
#include "Bridge.h"
#define NORTH 0
#define SOUTH 1
#define EMPTY 2
#define NARR 0
#define SARR 1
#define NMOV 2
#define SMOV 3
#define DEP 4

Bridge* new_Bridge(Engine* e) {
    Bridge* opt = malloc(sizeof(Bridge));
    opt->stat = EMPTY;
    opt->north_queue = new_Queue();
    opt->south_queue = new_Queue();
    opt->time = 0;
    opt->enroute = new_Queue();
    opt->engine = e;
    opt->is_grouped = 0;
    return opt;
}

int arrive(Bridge* b, int dir) {
    if (b == NULL) {
        return 1;
    }
    Car* c = new_Car(get_time(b->engine), dir);
    if (dir == NORTH) {
        enqueue(b->north_queue, c);
    } else {
        enqueue(b->south_queue, c);
    }

    if (b->stat == EMPTY) {
        b->time = gen_time();
        if (dir == NORTH) {
            schedule_event(b->engine, get_time(b->engine), NMOV, b);
            b->stat = NORTH;
        } else {
            schedule_event(b->engine, get_time(b->engine), SMOV, b);
            b->stat = SOUTH;
        }
    } else if (b->stat == dir) {
        if (dir == NORTH) {
            if (b->north_queue->head->delay != 0) {
                double time_mov = 0;
                Car* car = b->north_queue->head;
                for (int i = 0; i < b->north_queue->cnt - 1; i++) {
                    time_mov += car->delay;
                    car = car->next;
                }
                time_mov -= (get_time(b->engine) -
                    b->enroute->tail->time_start);
                schedule_event(b->engine, get_time(b->engine) +
                time_mov, NMOV, b);
                c->delay = gen_delay();
            }
        } else {
            if (b->south_queue->head->delay != 0) {
                double time_mov = 0;
                Car* car = b->south_queue->head;
                for (int i = 0; i < b->south_queue->cnt - 1; i++) {
                    time_mov += car->delay;
                    car = car->next;
                }
                schedule_event(b->engine, get_time(b->engine) +
                    time_mov, SMOV, b);
                c->delay = gen_delay();
            }
        }
    }
    return 0;
}

int move(Bridge* b, int dir) {
    if (b == NULL) {
        return 1;
    }
    Car* c;
    if (dir == NORTH) {
        c = dequeue(b->north_queue);
    } else {
        c = dequeue(b->south_queue);
    }
    b->stat = dir;
    enqueue(b->enroute, c);
    leave_queue(c, get_time(b->engine));
    schedule_event(b->engine, get_time(b->engine) + b->time, DEP, b);
    return 0;
}

int depart(Bridge* b) {
    if (b == NULL) {
        return 1;
    }
    Car* car = dequeue(b->enroute);
    leave_sys(car, get_time(b->engine));
    print_Car(car);
    if (b->enroute->cnt == 0) {
        if (b->stat == NORTH) {
            if (b->south_queue->cnt != 0) {
                b->stat = SOUTH;
                b->time = gen_time();
                double t = get_time(b->engine);
                Car* c = b->south_queue->head;
                for (int i = 0; i < b->south_queue->cnt; i++) {
                    schedule_event(b->engine, t, SMOV, b);
                    c->delay = gen_delay();
                    t += c->delay;
                    c = c->next;
                }
            } else {
                if (b->north_queue->cnt != 0) {
                    b->stat = NORTH;
                    b->time = gen_time();
                    double t = get_time(b->engine);
                    Car* c = b->north_queue->head;
                    for (int i = 0; i < b->north_queue->cnt; i++) {
                        schedule_event(b->engine, t, NMOV, b);
                        c->delay = gen_delay();
                        t += c->delay;
                        c = c->next;
                    }
                } else {
                    b->stat = EMPTY;
                }
            }
        } else {
            if (b->north_queue->cnt != 0) {
                b->stat = NORTH;
                b->time = gen_time();
                double t = get_time(b->engine);
                Car* c = b->north_queue->head;
                for (int i = 0; i < b->north_queue->cnt; i++) {
                    schedule_event(b->engine, t, NMOV, b);
                    c->delay = gen_delay();
                    t += c->delay;
                    c = c->next;

                }
            } else {
                if (b->south_queue->cnt != 0) {
                    b->stat = SOUTH;
                    b->time = gen_time();
                    double t = get_time(b->engine);
                    Car* c = b->south_queue->head;
                    for (int i = 0; i < b->south_queue->cnt; i++) {
                        schedule_event(b->engine, t, SMOV, b);
                        c->delay = gen_delay();
                        t += c->delay;
                        c = c->next;

                    }
                } else {
                    b->stat = EMPTY;
                }
            }
        }
    }
    free(car);
    return 0;
}

int free_Bridge(Bridge* b) {
    free_Queue(b->north_queue);
    free_Queue(b->south_queue);
    free_Queue(b->enroute);
    free_Engine(b->engine);
    free(b);
}
