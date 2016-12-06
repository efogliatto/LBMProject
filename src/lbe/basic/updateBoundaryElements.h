#ifndef UPDATEBOUNDARYELEMENTS_H
#define UPDATEBOUNDARYELEMENTS_H

#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>

void updateBoundaryElements( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // UPDATEBOUNDARYELEMENTS_H
