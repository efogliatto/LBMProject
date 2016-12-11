#ifndef RANDOMT_H
#define RANDOMT_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void randomT( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId );


#endif // RANDOMT_H
