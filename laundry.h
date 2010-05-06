#ifndef LAUNDRY_H
#define LAUNDRY_H

typedef struct slaundry * laundry;

laundry create_laundry(double tf, double tr, int n, int s, int o);

laundry destroy_laundry(laundry l);

void run_laundry(laundry l);

#endif

