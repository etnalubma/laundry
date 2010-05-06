#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "randomgen.h"
#include "laundry.h"

#define BITS 32

int main(){
    int *histogram;
    int iterations = 1000000;
    int i, j, n, s, o;
    double e, e2, t;
    randgen rg;
    laundry l;
    
    rg = create_rg(MZRAN13, 0, BITS);    
    
    n = 5;
    s = 2;
    o = 1;
    printf("Simulacion para %i lavarropas, %i repuestos, %i operarios\n", n, s, o);
    printf("Valores aleatorios \t Tiempo promedio (Meses) \t Desviacion estandar\n");        
    for(j=1; j<iterations; j*=10){
        e = 0;
        e2 = 0;
        histogram = calloc(100, sizeof(int));
        for(i=0; i<j; i++){
            l = create_laundry(1, 0.125, n, s, o, rg);        
            t = run_laundry(l);
            e += t/(double)j;
            e2 += (t*t)/(double)j;
            l = destroy_laundry(l);
            histogram[(int)t]++;
        }
        printf("\n");
        printf("%i \t\t\t %f \t\t\t %f\n", j, e, sqrt(e2-e*e));
        /*escribir a un .dat*/
        free(histogram);
    }

    rg = destroy_rg(rg);

    return 0;
}

