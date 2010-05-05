#ifndef EVENTS_H
#define EVENTS_H

#include "enode.h"

typedef struct sevents * events;

events create_events(void);

events destroy_events(events s);

void insert_event(events s, event e);

event next_event(events s);

#endif
