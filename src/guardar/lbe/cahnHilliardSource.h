#ifndef CAHNHILLIARDSOURCE_H
#define CAHNHILLIARDSOURCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void cahnHilliardSource(struct twoPhasesFields* fields, const struct solverInfo* info, double* sourceTerm, const unsigned int id);

#endif // CAHNHILLIARDSOURCE_H
