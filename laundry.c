#include "event.h"
#include "events.h"
#include "generators.h"
#include "laundry.h"

struct slaundry{
    events e;
    double trunning;
    double tfail;
    double trepair;
    int n;
    int s;
    int o;
};
