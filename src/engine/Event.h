typedef struct Event Event;

Event* new_Event(double time_stamp, int type, void* data);
double get_time_stamp(Event* e);
Event* get_parent(Event* e);
Event* get_left(Event* e);
Event* get_right(Event* e);