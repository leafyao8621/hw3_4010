#include "Engine.h"
#include <stdlib.h>
#include <stdio.h>

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

int schedule_event(Engine* engine, Event* e) {
    if (get_time_stamp(e) > engine->duration) {
        return 1;
    } else {
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
