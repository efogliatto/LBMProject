#ifndef SCALARFIELDLAPLACIAN_H
#define SCALARFIELDLAPLACIAN_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

double scalarFieldLaplacian( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id );

#endif // SCALARFIELDLAPLACIAN_H
