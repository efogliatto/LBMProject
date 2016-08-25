#ifndef SCALARFIELDGRADIENT_H
#define SCALARFIELDGRADIENT_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

double* scalarFieldGradient( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id );

#endif // SCALARFIELDGRADIENT_H
