#ifndef LIANGSOURCE_H
#define LIANGSOURCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangSource(struct twoPhasesFields* fields, struct solverInfo* info, double* sourceTerm, unsigned int id);

#endif // LIANGSOURCE_H
