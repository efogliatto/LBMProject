#ifndef TEMPERATURECOLLISION_H
#define TEMPERATURECOLLISION_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void temperatureCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // TEMPERATURECOLLISION_H
