#ifndef LIVELOCITY_LOCAL_H
#define LIVELOCITY_LOCAL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liVelocity_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // LIVELOCITY_LOCAL_H
