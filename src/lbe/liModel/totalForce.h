#ifndef FORCE_H
#define FORCE_H

#include <liModelInfo.h>
#include <interactionForce.h>

void totalForce( struct liModelInfo* info, double F[3], double* rho, int** nb, double* T, unsigned int id );

#endif // TOTALFORCE_H
