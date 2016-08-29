#ifndef LIANGTOTALFORCE_H
#define LIANGTOTALFORCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangTotalForce(struct twoPhasesFields* fields, struct solverInfo* info, double* eq, unsigned int id);

#endif // LIANGTOTALFORCE_H
