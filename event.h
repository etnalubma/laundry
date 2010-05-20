#ifndef EVENT_H
#define EVENT_H

typedef enum EVENT_TYPE {
    MACHINE_REPAIRED,
    MACHINE_BROKEN
} event_type;

typedef struct sevent * event;

/*
    Constructor de eventos.
    Parametros:
    @time Tiempo que falta para que ocurra el evento
    @type MACHINE_BROKEN | MACHINE_REPAIRED
*/
event create_event(double time, event_type type);

/*Destructor*/
event destroy_event(event e);

event_type get_type(event e);

double get_time(event e);

/*Actualiza el tiempo del evento*/
event update_time(event e, double time);

#endif
