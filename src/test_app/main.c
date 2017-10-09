#include "../engine/api.h"
#include "Point.h"
#include <stdlib.h>
#include <stdio.h>
Point* start;
Engine* engine;

int handle(Engine* engine, Event* event) {
    printf("%lf\n", get_time_stamp(event));
    if (get_type(event) == 1) {
        add(start, (Point*) get_data(event));
    } else {
        sub(start, (Point*) get_data(event));
    }
    free_Point(get_data(event));
    schedule_event(engine, get_time_stamp(event) + 3, 2, new_Point(1, 1));
    printf("%d, %d\n", start->x, start->y);
    return 0;
}
int main() {
    start = new_Point(0, 0);
    printf("%d, %d\n", start->x, start->y);
    engine = new_Engine(10);
    schedule_event(engine, 2.3, 1, new_Point(1, 1));

    schedule_event(engine, 3, 1, new_Point(2, 2));

    schedule_event(engine, 2, 1, new_Point(3, 3));
    schedule_event(engine, 4, 1, new_Point(4, 4));
    schedule_event(engine, 3, 1, new_Point(1, 1));
    schedule_event(engine, 1, 1, new_Point(3, 3));
    schedule_event(engine, 6, 1, new_Point(3, 3));
    schedule_event(engine, 0.5, 1, new_Point(4, 4));
    schedule_event(engine, 1, 1, new_Point(5, 5));
    main_loop(engine);
}
