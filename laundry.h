#ifndef LAUNDRY_H
#define LAUNDRY_H

typedef struct slaundry * laundry;

laundry create_laundry(double tf, double tr, int n, int s, int o, randgen rg);

laundry destroy_laundry(laundry l);

double run_laundry(laundry l);

#endif

