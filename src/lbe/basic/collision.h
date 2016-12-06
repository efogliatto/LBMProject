#ifndef COLLISION_H
#define COLLISION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void collision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // COLLISION_H
