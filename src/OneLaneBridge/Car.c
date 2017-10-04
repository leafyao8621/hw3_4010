#include <stdio.h>
#include <stdlib.h>
#include "Car.h"

Car* new_Car(double time_arr, int dir) {
    Car* opt = malloc(sizeof(Car));
    if (opt == NULL) {
        puts("Fatal error! Out of memory!");
        return NULL;
    }
    opt->time_arr = time_arr;
    opt->dir = dir;
    opt->next = NULL;
    opt->time_start = 0;
    opt->time_out = 0;
    opt->tiq = 0;
    opt->tis = 0;
    opt->delay = 0;
    return opt;
}

int leave_queue(Car* c, double time_start) {
    if (c == NULL) {
        return 1;
    }
    c->time_start = time_start;
    c->tiq = time_start - c->time_arr;
    return 0;
}

int leave_sys(Car* c, double time_out) {
    if (c == NULL) {
        return 1;
    }
    c->time_out = time_out;
    c->tis = time_out - c->time_arr;
    return 0;
}

int print_Car(Car* c) {
    if (c == NULL) {
        return 1;
    }

    printf("%s,%lf,%lf,%lf,%lf,%lf\n", c->dir ? "SOUTH" : "NORTH",
          c->time_arr, c->time_start, c->time_out, c->tiq, c->tis);
    return 0;
}
