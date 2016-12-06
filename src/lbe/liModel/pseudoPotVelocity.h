#ifndef PSEUDOPOTVELOCITY_H
#define PSEUDOPOTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void pseudoPotVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // PSEUDOPOTVELOCITY_H
