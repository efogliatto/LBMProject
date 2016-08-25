#ifndef DENSITY_H
#define DENSITY_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void density( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld );

#endif // DENSITY_H
