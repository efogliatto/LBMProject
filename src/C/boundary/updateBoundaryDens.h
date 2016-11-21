#ifndef UPDATEBOUNDARYDENS_H
#define UPDATEBOUNDARYDENS_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>

void updateBoundaryDens( struct bdInfo* bdElements, double** field, struct latticeInfo* lattice, struct macroFields* mfields );


#endif // UPDATEBOUNDARYDENS_H
