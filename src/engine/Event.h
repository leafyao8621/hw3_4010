typedef struct Event Event;

Event* new_Event(double time_stamp, int type, void* data);
double get_time_stamp(Event* e);
Event* get_parent(Event* e);
Event* get_left(Event* e);
Event* get_right(Event* e);
int set_parent(Event* e, Event* e1);
int set_left(Event* e, Event* e1);
int set_right(Event* e, Event* e1);
