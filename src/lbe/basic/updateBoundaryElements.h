#ifndef UPDATEBOUNDARYELEMENTS_H
#define UPDATEBOUNDARYELEMENTS_H

#include <bdInfo.h>
#include <lbeField.h>
#include <liModelInfo.h>
#include <macroFields.h>

void updateBoundaryElements( struct bdInfo* bdElements, struct lbeField* field, struct liModelInfo* info, struct macroFields* mfields, int** nb );

#endif // UPDATEBOUNDARYELEMENTS_H
