#ifndef VELOCITY_H
#define VELOCITY_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void velocity( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar** fld );

#endif // VELOCITY_H
