typedef struct Event Event;

Event* new_Event(double time_stamp, int type, void* data);
double get_time_stamp(Event* e);