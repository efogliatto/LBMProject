#ifndef TESTVELOCITY_LOCAL_H
#define TESTVELOCITY_LOCAL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void testVelocity_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // TESTVELOCITY_LOCAL_H
