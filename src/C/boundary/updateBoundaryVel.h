#ifndef UPDATEBOUNDARYVEL_H
#define UPDATEBOUNDARYVEL_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <liModelInfo.h>
#include <macroFields.h>

void updateBoundaryVel( struct liModelInfo* info, struct bdInfo* bdElements, double** field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb );


#endif // UPDATEBOUNDARYVEL_H
