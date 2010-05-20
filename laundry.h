#ifndef LAUNDRY_H
#define LAUNDRY_H

#include "randomgen.h"

typedef struct slaundry * laundry;

/*
    Constructor de una lavanderia
    Parametros:
    @tf Tiempo medio de falla
    @tr Tiempo medio de reparacion
    @n Cantidad de lavarropas
    @s Cantidad de repuestos
    @o Cantidad de operarios
    @rg Generador de numeros aleatorios
*/
laundry create_laundry(double tf, double tr, int n, int s, int o, randgen rg);


/*Destructor*/
laundry destroy_laundry(laundry l);

/*Corre la simulacion para una lavanderia y retorna el tiempo en que el sistema falla. */
double run_laundry(laundry l);

#endif

