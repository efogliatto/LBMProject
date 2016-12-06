#ifndef MACROTEMPERATURE_H
#define MACROTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void macroTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // MACROTEMPERATURE_H
