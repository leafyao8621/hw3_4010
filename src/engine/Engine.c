#include "Engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Engine {
    double time_now;
    double duration;
    FutureEventList* list;
};

Engine* new_Engine(double duration) {
    Engine* opt = malloc(sizeof(Engine));
    if (opt == NULL) {
        puts("Fatal error! Out of memory!");
        return NULL;
    }
    opt->time_now = 0;
    opt->duration = duration;
    opt->list = new_FutureEventList();
    if (opt->list == NULL) {
        puts("Fatal error! Out of memory!");
        return NULL;
    }
    return opt;
}

int schedule_event(Engine* engine, double time_stamp, int type, void* data) {
    if (time_stamp > engine->duration) {
        return 1;
    } else {
        Event* e = new_Event(time_stamp, type, data);
        schedule(engine->list, e);
        return 0;
    }
}

int main_loop(Engine* e) {
    while (get_cnt(e->list) > 0) {
        e->time_now = get_time_stamp(get_root(e->list));
        handle(e, get_root(e->list));
        remove_event(e->list);
    }
    return 0;
}

double get_time(Engine* e) {
    return e->time_now;
}

int free_Engine(Engine* e) {
    if (e == NULL) {
        return 1;
    }
    free(e->list);
    free(e);
    return 0;
}

double rand_unif(double lb, double ub) {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return lb + n * (ub - lb);
}

double rand_exp(double mean) {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return -mean * (log(1 - n));
}
