#ifndef ADIABATIC_H
#define ADIABATIC_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>

void adiabatic( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice, struct macroFields* mfields, int fid );


#endif // ADIABATIC_H
