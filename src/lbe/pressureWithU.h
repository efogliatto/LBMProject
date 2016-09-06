#ifndef PRESSUREWITHU_U
#define PRESSUREWITHU_U

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <scalarFieldGradient.h>

void pressureWithU( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* fld );

#endif // PRESSUREWITHU_U
