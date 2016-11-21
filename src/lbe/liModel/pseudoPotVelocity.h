#ifndef PSEUDOPOTVELOCITY_H
#define PSEUDOPOTVELOCITY_H

#include <liModelInfo.h>

void pseudoPotVelocity( struct liModelInfo* info, double* rho, double** v, double** f, int** nb, double* T );

#endif // PSEUDOPOTVELOCITY_H
