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

/*Inicializador del sistema*/
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

    /*Acumulador del tiempo en funcionamiento*/
    double trunning=0;
    
    int broken = 0, waiting = 0;

    /*Se inicializa el sistema*/
    l = init_laundry(l);
    while(broken <= (l->s)){
        /*Mientras la cantidad de maquinas rotas sea menor
        o igual a la cantidad de repuestos, el sistema puede
        funcionar.       
        */
        current = next_event(l->events_list);
        trunning += get_time(current);
        
        if(get_type(current) == MACHINE_BROKEN){
            /*El evento es una maquina rota, entonces
            se genera un nuevo tiempo de falla para uno
            los repuestos que entra en funcionamiento.
            */
            t = exponential(l->rg, 1./(l->tfail));
            e = create_event(t, MACHINE_BROKEN);
            l->events_list = insert_event(l->events_list, e);
            broken++;

            if(broken <= (l->o)){
                /*Si hay un operario libre, entonces se genera
                un nuevo tiempo de reparacion para la maquina que
                entra al taller.                
                */
                t = exponential(l->rg, 1./(l->trepair));
                e = create_event(t, MACHINE_REPAIRED);
                l->events_list = insert_event(l->events_list, e);
            }
            else{
                /*Si todos los operarios estan ocupados, la maquina
                queda en espera.
                */
                waiting++;
            }
        }
        else{
            /*El evento es una maquina reparada, entonces hay una maquina
            rota menos. Ademas se acaba de liberar un operario, entonces si hay
            maquinas en espera de reparacion, se genera un nuevo tiempo de 
            reparacion.
            */
            broken--;
            if(waiting > 0){
                waiting--;
                t = exponential(l->rg, 1./(l->trepair));
                e = create_event(t, MACHINE_REPAIRED);
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
        /*Se generan los `n` tiempos iniciales
        de falla y se los agrega a la lista de eventos
        */
        t = exponential(l->rg, 1./(l->tfail));     
        e = create_event(t, MACHINE_BROKEN);
        l->events_list = insert_event(l->events_list, e);
    }
    return l;
}
