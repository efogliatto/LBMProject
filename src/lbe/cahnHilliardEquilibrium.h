#ifndef CAHNHILLIARDEQUILIBRIUM_H
#define CAHNHILLIARDEQUILIBRIUM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void cahnHilliardEquilibrium(struct twoPhasesFields* fields, const struct solverInfo* info, double* eq, const unsigned int id);

#endif // CAHNHILLIARDEQUILIBRIUM_H
