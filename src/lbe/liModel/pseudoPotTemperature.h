#ifndef PSEUDOPOTTEMPERATURE_H
#define PSEUDOPOTTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void pseudoPotTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // PSEUDOPOTTEMPERATURE_H
