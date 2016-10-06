#ifndef WRITEPDFTOVTK_H
#define WRITEPDFTOVTK_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

void writePdfToVTK( char* fname, double** field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time );

#endif // WRITEPDFTOVTK_H
