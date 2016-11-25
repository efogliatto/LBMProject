#ifndef BOUNCEBACK_H 
#define BOUNCEBACK_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <lbeField.h>

void bounceBack( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, int** nb, int bndId );


#endif // BOUNCEBACK_H
