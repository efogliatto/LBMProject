#ifndef SCALARFIELDLAPLACIAN_H
#define SCALARFIELDLAPLACIAN_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

c_scalar scalarFieldLaplacian( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* fld, int id );

#endif // SCALARFIELDLAPLACIAN_H
