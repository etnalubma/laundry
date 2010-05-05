#ifndef ENODE_H
#define ENODE_H

#include "event.h"

typedef struct senode * enode;

enode create_enode(event e);

enode destroy_enode(enode e);

#endif
