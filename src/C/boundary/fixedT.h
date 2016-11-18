#ifndef FIXEDT_H
#define FIXEDT_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>

void fixedT( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice, struct macroFields* mfields, int fid );


#endif // FIXEDT_H
