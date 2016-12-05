#ifndef EQUILIBRIUM_H
#define EQUILIBRIUM_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void equilibrium( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );


#endif // EQUILIBRIUM_H
