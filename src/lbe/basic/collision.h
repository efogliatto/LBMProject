#ifndef COLLISION_H
#define COLLISION_H

#include <macroFields.h>
#include <lbeField.h>
#include <liModelInfo.h>

void collision( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb );

#endif // COLLISION_H
