#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Bridge.h"
#define NORTH 0
#define SOUTH 1
#define EMPTY 2
#define NARR 0
#define SARR 1
#define NMOV 2
#define SMOV 3
#define DEP 4

double rate;
double tlb;
double tub;
double dlb;
double dub;
Bridge* b;

double gen_time() {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return tlb + n * (tub - tlb);
}

double gen_delay() {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return dlb + n * (dub - dlb);
}

double gen_int_arr() {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return -rate * (log(1 - n));
}

int handle(Engine* engine, Event* event) {
    if (engine == NULL || event == NULL) {
        return 1;
    }
    if (event->type == NARR) {
        arrive(b, NORTH);
    } else if (event->type == SARR) {
        arrive(b, SOUTH);
    } else if (event->type == NMOV) {
        move(b, NORTH);
    } else if (event->type == SMOV) {
        move(b, SOUTH);
    } else if (event->type == DEP) {
        depart(b);
    }
    return 0;
}

int main(int argc, const char** argv) {
    if (argc < 7) {
        puts("Not enough # of arguments.");
        return 1;
    }
    rate = atof(argv[1]);
    tlb = atof(argv[2]);
    tub = atof(argv[3]);
    dlb = atof(argv[4]);
    dub = atof(argv[5]);
    double dur = atof(argv[6]);
    if (rate <= 0 || tlb <= 0 || tub < 0 || tlb >= tub ||
        dlb <= 0 || dub < 0 || dlb >= dub || dur <= 0) {
        puts("Invalid argument(s)!");
        return 1;
    }
    Engine* e = new_Engine(dur);
    b = new_Bridge(e);
    srand(time(NULL));
    double t = 0;
    while (t < dur) {
        t += gen_int_arr();
        schedule_event(e, new_Event(t, NARR, b));
    }
    t = 0;
    while (t < dur) {
        t += gen_int_arr();
        schedule_event(e, new_Event(t, SARR, b));
    }
    puts("Dir,Time_Arr,Time_Mov,Time_Out,TIQ,TIS");
    main_loop(e);
    free_Bridge(b);
    return 0;
}
