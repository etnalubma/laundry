#ifndef EVENT_H
#define EVENT_H

typedef enum EVENT_TYPE {
    machine_repaired,
    machine_broken
} event_type;

typedef struct sevent * event;

event create_event(double time, event_type type);

event destroy_event(event e);

event_type get_type(event e);

double get_time(event e);

event update_time(event e, double time);

#endif
