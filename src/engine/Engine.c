#include "Engine.h"
#include <stdlib.h>
#include <stdio.h>
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
    if (e->time_stamp > engine->duration) {
        return 1;
    } else {
        schedule(engine->list, e);
        return 0;
    }
}

int main_loop(Engine* e) {
    while (e->list->cnt > 0) {
        e->time_now = e->list->root->time_stamp;
        handle(e, e->list->root);
        remove_event(e->list);
    }
    return 0;
}
