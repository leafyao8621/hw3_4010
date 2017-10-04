#include "Event.h"
typedef struct FutureEventList {
    Event* root;
    Event* last;
    int cnt;
} FutureEventList;

FutureEventList* new_FutureEventList();
int schedule(FutureEventList* f, Event* e);
int remove_event(FutureEventList* f);
