#ifndef WRITESCALARTOVTK_H
#define WRITESCALARTOVTK_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

void writeScalarToVTK( char* fname, double* field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time );

#endif // WRITESCALARTOVTK_H
