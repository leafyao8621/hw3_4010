#include "Event.h"
typedef struct FutureEventList FutureEventList;

FutureEventList* new_FutureEventList();
int schedule(FutureEventList* f, Event* e);
int remove_event(FutureEventList* f);
int get_cnt(FutureEventList* f);
Event* get_root(FutureEventList* f);