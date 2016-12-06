#ifndef INTERACTIONFORCE_H
#define INTERACTIONFORCE_H

#include <latticeMesh.h>

void interactionForce( struct latticeMesh* mesh, double F[3], double* rho, double* T, unsigned int id );

#endif // INTERACTIONFORCE_H
