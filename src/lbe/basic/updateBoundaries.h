#ifndef UPDATEBOUNDARIES_H
#define UPDATEBOUNDARIES_H

#include <bounceBack.h>
#include <fixedT.h>
#include <fixedU.h>
#include <adiabatic.h>
#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>

void updateBoundaries( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // UPDATEBOUNDARIES_H
