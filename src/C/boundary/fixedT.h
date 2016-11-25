#ifndef FIXEDT_H
#define FIXEDT_H

#include <bdInfo.h>
#include <latticeInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void fixedT( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId );


#endif // FIXEDT_H
