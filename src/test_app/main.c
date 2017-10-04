#include "../engine/api.h"
#include "Point.h"
#include <stdlib.h>
#include <stdio.h>
Point* start;
Engine* engine;

int handle(Engine* engine, Event* event) {
    printf("%lf\n", event->time_stamp);
    if (event->type == 1) {
        add(start, (Point*) event->data);
    } else {
        sub(start, (Point*) event->data);
    }
    free_Point(event->data);
    //Event* newe = new_Event(event->time_stamp + 3, event->type, new_Point(1, 1));
    //schedule_event(engine, newe);
    printf("%d, %d\n", start->x, start->y);
    return 0;
}
int main() {
    start = new_Point(0, 0);
    printf("%d, %d\n", start->x, start->y);
    engine = new_Engine(10);
    Event* e0 = new_Event(2.3, 1, new_Point(1, 1));
    Event* e1 = new_Event(3, 2, new_Point(2, 2));
    Event* e2 = new_Event(2, 1, new_Point(3, 3));
    Event* e3 = new_Event(4, 1, new_Point(4, 4));
    Event* e4 = new_Event(1, 1, new_Point(3, 3));
    Event* e5 = new_Event(6, 2, new_Point(3, 3));
    Event* e6 = new_Event(0.5, 1, new_Point(4, 4));
    Event* e7 = new_Event(3, 1, new_Point(1, 1));
    schedule_event(engine, e0);
    schedule_event(engine, e1);
    schedule_event(engine, e2);
    schedule_event(engine, e3);
    schedule_event(engine, e4);
    schedule_event(engine, e5);
    schedule_event(engine, e6);
    schedule_event(engine, e7);
    schedule_event(engine, new_Event(2, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(7, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(1.1, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(7, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(7, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(7, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(7, 1, new_Point(0.22, 0.1)));
    schedule_event(engine, new_Event(0.1, 1, new_Point(0.22, 0.1)));
    printf("%lf\n", engine->list->last->parent->parent->right->parent->parent->right->right->parent->left->parent->parent->parent->left->parent->right->left->left->parent->right->parent->time_stamp);
    //main_loop(engine);
}
