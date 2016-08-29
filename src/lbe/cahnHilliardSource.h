#ifndef CAHNHILLIARDSOURCE_H
#define CAHNHILLIARDSOURCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void cahnHilliardSource(struct twoPhasesFields* fields, struct solverInfo* info, double* sourceTerm, unsigned int id);

#endif // CAHNHILLIARDSOURCE_H
