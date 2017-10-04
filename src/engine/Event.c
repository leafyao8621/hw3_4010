#include <stdlib.h>
#include <stdio.h>
#include "Event.h"
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
