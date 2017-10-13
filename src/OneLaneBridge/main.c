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

double nrate;
double srate;
double tlb;
double tub;
double dlb;
double dub;
Bridge* b;

double gen_time() {
    return rand_unif(tlb, tub);
}

double gen_delay() {
    return rand_unif(dlb, dub);
}

double gen_n_int_arr() {
    return rand_exp(nrate);
}

double gen_s_int_arr() {
    return rand_exp(srate);
}

int handle(Engine* engine, Event* event) {
    if (engine == NULL || event == NULL) {
        return 1;
    }
    if (get_type(event) == NARR) {
        arrive(b, NORTH);
    } else if (get_type(event) == SARR) {
        arrive(b, SOUTH);
    } else if (get_type(event) == NMOV) {
        move(b, NORTH);
    } else if (get_type(event) == SMOV) {
        move(b, SOUTH);
    } else if (get_type(event) == DEP) {
        depart(b);
    }
    return 0;
}

int main(int argc, const char** argv) {
    if (argc < 8) {
        puts("Not enough # of arguments.");
        return 1;
    }
    nrate = atof(argv[1]);
    srate = atof(argv[2]);
    tlb = atof(argv[3]);
    tub = atof(argv[4]);
    dlb = atof(argv[5]);
    dub = atof(argv[6]);
    double dur = atof(argv[7]);
    if (nrate <= 0 || srate <= 0 || tlb <= 0 || tub < 0 || tlb >= tub ||
        dlb <= 0 || dub < 0 || dlb >= dub || dur <= 0) {
        puts("Invalid argument(s)!");
        return 1;
    }
    Engine* e = new_Engine(dur);
    b = new_Bridge(e);
    srand(time(NULL));
    double t = 0;
    while (t < dur) {
        t += gen_n_int_arr();
        schedule_event(e, t, NARR, b);
    }
    t = 0;
    while (t < dur) {
        t += gen_s_int_arr();
        schedule_event(e, t, SARR, b);
    }
    puts("Dir,TimeArr,TimeMov,TimeOut,TIQ,TIS");
    main_loop(e);
    free_Bridge(b);
    return 0;
}
