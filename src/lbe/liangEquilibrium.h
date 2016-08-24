#ifndef LIANGEQUILIBRIUM_H
#define LIANGEQUILIBRIUM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangEquilibrium(struct twoPhasesFields* fields, const struct solverInfo* info, double* eq, const unsigned int id);

#endif // LIANGEQUILIBRIUM_H
