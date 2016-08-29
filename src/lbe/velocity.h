#ifndef VELOCITY_H
#define VELOCITY_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void velocity( struct twoPhasesFields* fields, struct solverInfo* info, double** fld );

#endif // VELOCITY_H
