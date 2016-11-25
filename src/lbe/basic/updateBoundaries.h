#ifndef UPDATEBOUNDARIES_H
#define UPDATEBOUNDARIES_H

#include <bounceBack.h>
#include <fixedT.h>
#include <adiabatic.h>
#include <lbeField.h>
#include <macroFields.h>

void updateBoundaries( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb );

#endif // UPDATEBOUNDARIES_H
