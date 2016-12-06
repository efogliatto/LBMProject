#ifndef LITEMPERATURE_LOCAL_H
#define LITEMPERATURE_LOCAL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liTemperature_local( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // LITEMPERATURE_LOCAL_H
