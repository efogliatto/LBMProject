#ifndef SCALARFIELDLAPLACIAN_H
#define SCALARFIELDLAPLACIAN_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

double scalarFieldLaplacian( struct twoPhasesFields* fields, struct solverInfo* info, double* fld, int id );

#endif // SCALARFIELDLAPLACIAN_H
