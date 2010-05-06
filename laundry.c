#include <stdlib.h>
#include <stdio.h>

#include "event.h"
#include "events.h"
#include "generators.h"
#include "laundry.h"

struct slaundry{
    events events_list;
    double tfail;
    double trepair;
    int n;
    int s;
    int o;
    randgen rg;
};

laundry init_laundry(laundry l);

laundry create_laundry(double tf, double tr, int n, int s, int o, randgen rg){
    laundry l;
    l = (laundry)calloc(1, sizeof(struct slaundry));

    l->events_list = create_events();
    l->tfail = tf;
    l->trepair = tr;
    l->n = n;
    l->s = s;
    l->o = o;
    l->rg = rg;

    return l;
}

laundry destroy_laundry(laundry l){
    l->events_list = destroy_events(l->events_list);
    free(l);
    l = NULL;
    return l;
}

double run_laundry(laundry l){
    event current, e;
    double t;    
    double trunning=0;
    int broken = 0, waiting = 0;

    l = init_laundry(l);
    while(broken <= l->s){
        current = next_event(l->events_list);
        trunning += get_time(current);
        
        if(get_type(current) == machine_broken){
            t = exponential(l->rg, 1./(l->tfail));
            e = create_event(t, machine_broken);
            l->events_list = insert_event(l->events_list, e);
            broken++;

            if(broken <= l->o){
                t = exponential(l->rg, 1./(l->trepair));
                e = create_event(t, machine_repaired);
                l->events_list = insert_event(l->events_list, e);
            }
            else{
                waiting++;
            }
        }
        else{
            broken--;
            if(waiting > 0){
                waiting--;
                t = exponential(l->rg, 1./(l->trepair));
                e = create_event(t, machine_repaired);
                l->events_list = insert_event(l->events_list, e);
            }
        }
        destroy_event(current);
    }
    
    return trunning;
}

laundry init_laundry(laundry l){
    int i;
    double t;
    event e;
    int n = l->n;
    
    for(i=0; i<n; i++){
        t = exponential(l->rg, 1./(l->tfail));     
        e = create_event(t, machine_broken);
        l->events_list = insert_event(l->events_list, e);
    }
    return l;
}
