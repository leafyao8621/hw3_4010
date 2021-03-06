#include <stdlib.h>
#include <stdio.h>
#include "Event.h"

struct Event {
    double time_stamp;
    struct Event* parent;
    struct Event* left;
    struct Event* right;
    int type;
    void* data;
};

//creates a new event and sets its corresponding fields
Event* new_Event(double time_stamp, int type, void* data) {
    Event* opt = malloc(sizeof(Event));
    if (opt == NULL) {
        puts("Fatal error! Out of Memory!");
        return NULL;
    }
    opt->time_stamp = time_stamp;
    opt->type = type;
    opt->data = data;
    opt->parent = NULL;
    opt->left = NULL;
    opt->right = NULL;
    return opt;
}

double get_time_stamp(Event* e) {
    return e->time_stamp;
}

int get_type(Event* e) {
    return e->type;
}

void* get_data(Event* e) {
    return e->data;
}

Event* get_parent(Event* e) {
    if (e == NULL) {
        return NULL;
    }
    return e->parent;
}

Event* get_left(Event* e) {
    if (e == NULL) {
        return NULL;
    }
    return e->left;
}

Event* get_right(Event* e) {
    if (e == NULL) {
        return NULL;
    }
    return e->right;
}

int set_parent(Event* e, Event* e1) {
    if (e == NULL) {
        return 1;
    }
    e->parent = e1;
    return 0;
}

int set_left(Event* e, Event* e1) {
    if (e == NULL) {
        return 1;
    }
    e->left = e1;
    return 0;
}

int set_right(Event* e, Event* e1) {
    if (e == NULL) {
        return 1;
    }
    e->right = e1;
    return 0;
}
