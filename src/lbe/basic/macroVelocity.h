#ifndef MACROVELOCITY_H
#define MACROVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void macroVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // MACROVELOCITY_H
