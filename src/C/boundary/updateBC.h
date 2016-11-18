#ifndef UPDATEBC_H
#define UPDATEBC_H

#include <bounceBack.h>
#include <fixedT.h>

void updateBC( struct bdInfo* bdElements, int** nb, double** field, char* fname, struct latticeInfo* lattice, struct macroFields* mfields );

#endif // UPDATEBC_H
