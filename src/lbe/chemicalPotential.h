#ifndef CHEMICALPOTENTIAL_H
#define CHEMICALPOTENTIAL_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <scalarFieldLaplacian.h>

void chemicalPotential( struct twoPhasesFields* fields, struct solverInfo* info, double* chfield );

#endif // CHEMICALPOTENTIAL_H
