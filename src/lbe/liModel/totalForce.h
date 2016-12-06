#ifndef FORCE_H
#define FORCE_H

#include <liModelInfo.h>
#include <interactionForce.h>
#include <latticeMesh.h>

void totalForce( struct latticeMesh* mesh, double F[3], double* rho, double* T, unsigned int id );

#endif // TOTALFORCE_H
