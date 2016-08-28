#ifndef SYNCSCALARFIELD_H
#define SYNCSCALARFIELD_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void syncScalarField( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld );

#endif // SYNCSCALARFIELD_H
