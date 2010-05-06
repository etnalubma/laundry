#include <stdio.h>
#include "events.h"

int main(){
    event e1, e2, e3, e4;
    events s = create_events();

    e1 = create_event(1.2, machine_broken);
    e2 = create_event(1.1, machine_broken);
    e3 = create_event(1.15, machine_broken);
    e4 = create_event(1.3, machine_broken);

    insert_event(s, e1);
    insert_event(s, e2);
    insert_event(s, e3);
    insert_event(s, e4);

    printf("%f\n", get_time(next_event(s)));
    printf("%f\n", get_time(next_event(s)));
    printf("%f\n", get_time(next_event(s)));
    printf("%f\n", get_time(next_event(s)));

    destroy_events(s);
    
    return 0;
}

