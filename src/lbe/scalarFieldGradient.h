#ifndef SCALARFIELDGRADIENT_H
#define SCALARFIELDGRADIENT_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

double* scalarFieldGradient( struct twoPhasesFields* fields, struct solverInfo* info, double* fld, int id );

#endif // SCALARFIELDGRADIENT_H
