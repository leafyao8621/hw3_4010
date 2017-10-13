typedef struct Event Event;
typedef struct FutureEventList FutureEventList;
typedef struct Engine Engine;
/*schedules an event to the engine*/
int schedule_event(Engine* engine, double time_stamp, int type, void* data);
/*creates a new engine*/
Engine* new_Engine(double duration);
/*prototype for event handler. to be implemented in application*/
int handle(Engine* engine, Event* event);
/*the "main loop". start the simulation using this function*/
int main_loop(Engine* e);
/*get the data from an event*/
void* get_data(Event* e);
/*get event type from an event*/
int get_type(Event* e);
/*get time stamp from an event*/
double get_time_stamp(Event* e);
/*get the current time from the engine*/
double get_time(Engine* e);
/*frees the memory allocated to the engine*/
int free_Engine(Engine* e);
/*generates a number from uniform distribution*/
double rand_unif(double lb, double ub);
/*generates a number from exponential distribution*/
double rand_exp(double mean);
