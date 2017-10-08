typedef struct Event Event;
typedef struct FutureEventList FutureEventList;
typedef struct Engine Engine;

FutureEventList* new_FutureEventList();
int schedule_event(Engine* engine, double time_stamp, int type, void* data);
Engine* new_Engine(double duration);
int handle(Engine* engine, Event* event);
int main_loop(Engine* e);
void* get_data(Event* e);
int get_type(Event* e);
double get_time_stamp(Event* e);
double get_time(Engine* e);
int free_Engine(Engine* e);
double rand_unif(double lb, double ub);
double rand_exp(double mean);
