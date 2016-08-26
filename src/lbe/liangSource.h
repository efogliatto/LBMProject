#ifndef LIANGSOURCE_H
#define LIANGSOURCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangSource(struct twoPhasesFields* fields, const struct solverInfo* info, double* sourceTerm, const unsigned int id);

#endif // LIANGSOURCE_H
