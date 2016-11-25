#ifndef LISRTCOLLISION_H
#define LISRTCOLLISION_H

#include <macroFields.h>
#include <lbeField.h>
#include <liModelInfo.h>

void liSRTCollision( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb );

#endif // LISRTCOLLISION_H
