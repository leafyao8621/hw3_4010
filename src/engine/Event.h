typedef struct Event {
    double time_stamp;
    struct Event* parent;
    struct Event* left;
    struct Event* right;
    int type;
    void* data;
} Event;

Event* new_Event(double time_stamp, int type, void* data);
