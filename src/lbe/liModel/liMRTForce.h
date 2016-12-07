#ifndef LIMRTFORCE_H
#define LIMRTFORCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void liMRTForce( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, double* S, unsigned int id );

#endif // LIMRTFORCE_H
