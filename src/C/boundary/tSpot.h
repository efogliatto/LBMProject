#ifndef TSPOT_H
#define TSPOT_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void tSpot( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId );


#endif // TSPOT_H
