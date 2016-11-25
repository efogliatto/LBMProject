#ifndef ADIABATIC_H
#define ADIABATIC_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void adiabatic( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId );

#endif // ADIABATIC_H
