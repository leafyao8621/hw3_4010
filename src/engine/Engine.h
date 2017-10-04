#include "FutureEventList.h"
typedef struct Engine {
    double time_now;
    double duration;
    FutureEventList* list;
} Engine;

Engine* new_Engine(double duration);
int schedule_event(Engine* engine, Event* e);
int handle(Engine* engine, Event* event);
int main_loop(Engine* e);
