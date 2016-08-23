#ifndef GRADIENT_H
#define GRADIENT_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

const double* gradient( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id );

#endif // GRADIENT_H
