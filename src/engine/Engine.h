#include "FutureEventList.h"
typedef struct Engine Engine;

Engine* new_Engine(double duration);
int schedule_event(Engine* engine, double time_stamp, int type, void* data);
int handle(Engine* engine, Event* event);
int main_loop(Engine* e);
double get_time(Engine* e);
int free_Engine(Engine* e);
