#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include "randomgen.h"
#include "laundry.h"

#define BITS 32

void print_use(char *pname)
{
    printf("Uso: %s opciones [ argumentos ...]\n", pname);
    printf("    -h  --help                  Enseña esta ayuda\n"
           "    -f  --file       fichero        Escribe la salida al fichero\n"
           "    -o  --operaries  numero         Configura la cantidad de operarios\n"
           "    -m  --machines   numero         Configura la cantidad de lavarropas\n"
           "    -s  --services   numero         Configura la gantidad de repuestos\n");
}

static struct option long_options[] =
 {
       /* These options don't set a flag.
          We distinguish them by their indices. */
       {"help", required_argument, 0, 'h'},          
       {"operaries", required_argument, 0, 'o'},
       {"machines",  required_argument, 0, 'm'},
       {"services",   required_argument, 0, 's'},
       {"file",      required_argument, 0, 'f'},
       {0, 0, 0, 0}
 };



int main(int argc, char *argv[]){
    int iterations = 100000;
    int i, j, m, s, o, next_option;
    char *output_file = NULL;
    FILE *file;
    double e, e2, t;
    randgen rg;
    laundry l;
  
    /*Cantidad de lavarropas*/
    m = 5;
    /*Cantidad de repuestos*/
    s = 2;
    /*Cantidad de operarios*/
    o = 1;

    /* Si se ejecuta sin parámetros ni opciones */
    if (argc == 1)
    {
        print_use(argv[0]);
        exit(EXIT_SUCCESS);
    }
    while (1)
    {
        /* Llamamos a la función getopt */
        next_option = getopt_long (argc, argv, "ho:m:s:f:", long_options, NULL);

        if (next_option == -1)
          break; /* No hay más opciones. Rompemos el bucle */

        switch (next_option)
        {
          case 'h' : /* -h o --help */
              print_use(argv[0]);
              exit(EXIT_SUCCESS);

          case 'm' : /* -m  o --machines */
              sscanf(optarg, "%d", &m); 
              break;              

          case 'o' : /* -o ó --operaries */
              sscanf(optarg, "%d", &o);
              break;              

          case 's' : /* -s o --services */
              sscanf(optarg, "%d", &s);
              break;              

          case 'f' : /* -f o --file */
              output_file = optarg; 
              break;

          case -1 : /* No hay más opciones */
              break;

          default : /* Algo más? No esperado. Abortamos */
              abort();
        }
    }
    
    if (output_file == NULL) {
        printf("Argumento --file requerido.\n");
        print_use(argv[0]);
        exit(EXIT_SUCCESS);
    }
    
    rg = create_rg(MZRAN13, 0, BITS);        

    printf("Simulacion para %i lavarropas, %i repuestos, %i operarios\n", m, s, o);
    printf("Valores aleatorios \t Tiempo promedio (Meses) \t Desviacion estandar\n");        

    file = fopen(output_file, "w");
    
    for(j=1; j<iterations; j*=10){
        e = 0;
        e2 = 0;
        
        for(i=0; i<j; i++){
            l = create_laundry(1, 0.125, m, s, o, rg);        
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

