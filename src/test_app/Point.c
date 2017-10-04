#include "Point.h"
#include <stdlib.h>
Point* new_Point(int x, int y) {
    Point* opt = malloc(sizeof(Point));
    opt->x = x;
    opt->y = y;
    return opt;
}

void add(Point* a, Point* b) {
    a->x += b->x;
    a->y += b->y;
}

void sub(Point* a, Point* b) {
    a->x -= b->x;
    a->y -= b->y;
}

void free_Point(Point* p) {
    free(p);
}
