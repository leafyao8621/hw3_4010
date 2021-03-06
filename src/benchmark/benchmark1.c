#include "../engine/FutureEventList.h"
#include "../sample/sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double rand_exp(double mean) {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return -mean * (log(1 - n));
}

double rand_unif(double lb, double ub) {
    double n = ((double) rand()) / ((double) RAND_MAX);
    return lb + n * (ub - lb);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        puts("Not enough args");
        return 1;
    }
    int init_size = atoi(argv[1]);
    if (init_size <= 0) {
        puts("Invalid initial size");
        return 1;
    }
    FutureEventList* f = new_FutureEventList();
    srand(time(NULL));
    /*initialize both FEL's*/
    for (int i = 0; i < init_size; i++) {
        double ts = rand_unif(0, 2);
        schedule(f, new_Event(ts, 1, NULL));
        Schedule(ts, NULL);
    }
    clock_t start = clock();
    /*hold operation for heap implementation*/
    for (int i = 0; i < 100000; i++) {
        schedule(f, new_Event(get_time_stamp(get_root(f)) + rand_exp(1), 1,
        NULL));
        remove_event(f);

    }
    clock_t end = clock();
    double t_time = ((double) end - (double) start) / CLOCKS_PER_SEC;
    printf("%d,%lf,", init_size, t_time);
    start = clock();
    /*hold operation for list implementation*/
    for (int i = 0; i < 100000; i++) {
        Event* e = Remove();
        Schedule(get_time(e) + rand_exp(1), NULL);
        free(e);
    }
    end = clock();
    t_time = ((double) end - (double) start) / CLOCKS_PER_SEC;
    printf("%lf\n", t_time);
    free_FutureEventList(f);
    return 0;
}