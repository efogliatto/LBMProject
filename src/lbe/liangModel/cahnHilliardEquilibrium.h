#ifndef CAHNHILLIARDEQUILIBRIUM_H
#define CAHNHILLIARDEQUILIBRIUM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void cahnHilliardEquilibrium(struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* eq, unsigned int id);

#endif // CAHNHILLIARDEQUILIBRIUM_H
