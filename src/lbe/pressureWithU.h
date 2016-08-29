#ifndef PRESSUREWITHU_U
#define PRESSUREWITHU_U

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <scalarFieldGradient.h>

void pressureWithU( struct twoPhasesFields* fields, struct solverInfo* info, double* fld );

#endif // PRESSUREWITHU_U
