typedef struct Event Event;
typedef struct FutureEventList FutureEventList;
typedef struct Engine Engine;

Event* new_Event(double time_stamp, int type, void* data);
FutureEventList* new_FutureEventList();
int schedule_event(Engine* engine, Event* e);
Engine* new_Engine(double duration);
int handle(Engine* engine, Event* event);
int main_loop(Engine* e);
