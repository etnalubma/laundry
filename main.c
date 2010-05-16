#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "randomgen.h"
#include "laundry.h"

#define BITS 32

int main(){
    int iterations = 100000;
    int i, j, n, s, o;
    FILE *file;
    double e, e2, t;
    randgen rg;
    laundry l;
  
    rg = create_rg(MZRAN13, 0, BITS);    

    /*Cantidad de lavarropas*/
    n = 5;
    /*Cantidad de repuestos*/
    s = 2;
    /*Cantidad de operarios*/
    o = 1;
    
    printf("Simulacion para %i lavarropas, %i repuestos, %i operarios\n", n, s, o);
    printf("Valores aleatorios \t Tiempo promedio (Meses) \t Desviacion estandar\n");        

    file = fopen("histogram.dat", "w");
    
    for(j=1; j<iterations; j*=10){
        e = 0;
        e2 = 0;
        
        for(i=0; i<j; i++){
            l = create_laundry(1, 0.125, n, s, o, rg);        
            t = run_laundry(l);
            e += t/(double)j;
            e2 += (t*t)/(double)j;
            l = destroy_laundry(l);
            if(j==10000)
                fprintf(file, "%f\n", t);
        }
        printf("\n");
        printf("%i \t\t\t %f \t\t\t %f\n", j, e, sqrt(e2-e*e));                                
    }

    fclose(file);   
    rg = destroy_rg(rg);

    return 0;
}

