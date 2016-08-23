#ifndef LAPLACIAN_H
#define LAPLACIAN_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

const double laplacian( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id );

#endif // LAPLACIAN_H
