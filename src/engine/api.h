typedef struct Event {
    double time_stamp;
    struct Event* parent;
    struct Event* left;
    struct Event* right;
    int type;
    void* data;
} Event;

typedef struct FutureEventList {
    Event* root;
    Event* last;
    int cnt;
} FutureEventList;

typedef struct Engine {
    double time_now;
    double duration;
    FutureEventList* list;
} Engine;

Event* new_Event(double time_stamp, int type, void* data);
FutureEventList* new_FutureEventList();
int schedule_event(Engine* engine, Event* e);
Engine* new_Engine(double duration);
int handle(Engine* engine, Event* event);
int main_loop(Engine* e);
