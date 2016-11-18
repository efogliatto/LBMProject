#ifndef BOUNCEBACK_H 
#define BOUNCEBACK_H

#include <bdInfo.h>
#include <latticeInfo.h>

void bounceBack( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice );


#endif // BOUNCEBACK_H
