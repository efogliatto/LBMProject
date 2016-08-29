#ifndef LIANGTOTALFORCE_H
#define LIANGTOTALFORCE_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>

void liangTotalForce(struct twoPhasesFields* fields, const struct solverInfo* info, double* eq, const unsigned int id);

#endif // LIANGTOTALFORCE_H
