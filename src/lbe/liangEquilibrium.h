#ifndef LIANGEQUILIBRIUM_H
#define LIANGEQUILIBRIUM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangEquilibrium(struct twoPhasesFields* fields, struct solverInfo* info, double* eq, unsigned int id);

#endif // LIANGEQUILIBRIUM_H
