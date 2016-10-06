#ifndef WRITEVECTORTOVTK_H
#define WRITEVECTORTOVTK_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

void writeVectorToVTK( char* fname, double** field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time );

#endif // WRITEVECTORTOVTK_H
