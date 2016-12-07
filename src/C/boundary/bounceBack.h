#ifndef BOUNCEBACK_H 
#define BOUNCEBACK_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <lbeField.h>
#include <macroFields.h>

void bounceBack( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, int** nb, int bndId,struct macroFields* mfields );


#endif // BOUNCEBACK_H
