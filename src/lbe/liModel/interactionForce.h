#ifndef INTERACTIONFORCE_H
#define INTERACTIONFORCE_H

#include <liModelInfo.h>

void interactionForce( struct liModelInfo* info, double F[3], double* rho, int** nb, double* T, unsigned int id );

#endif // INTERACTIONFORCE_H
