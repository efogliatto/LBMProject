#ifndef FIXEDU_H
#define FIXEDU_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void fixedU( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId );


#endif // FIXEDU_H
