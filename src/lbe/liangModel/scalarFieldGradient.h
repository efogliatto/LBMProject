#ifndef SCALARFIELDGRADIENT_H
#define SCALARFIELDGRADIENT_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

c_scalar* scalarFieldGradient( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* fld, int id );

#endif // SCALARFIELDGRADIENT_H
