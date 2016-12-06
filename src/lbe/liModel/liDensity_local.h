#ifndef LIDENSITY_LOCAL_H
#define LIDENSITY_LOCAL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liDensity_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // LIDENSITY_LOCAL_H
