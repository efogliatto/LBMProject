#ifndef LIVELOCITY_LOCAL_H
#define LIVELOCITY_LOCAL_H

#include <liModelInfo.h>

void liVelocity_local( struct liModelInfo* info, double* rho, double** v, double** f, int** nb, double* T, unsigned int id );

#endif // LIVELOCITY_LOCAL_H
