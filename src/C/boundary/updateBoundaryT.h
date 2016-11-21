#ifndef UPDATEBOUNDARYT_H
#define UPDATEBOUNDARYT_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>

void updateBoundaryT( struct bdInfo* bdElements, double** field, struct latticeInfo* lattice, struct macroFields* mfields );


#endif // UPDATEBOUNDARYT_H
