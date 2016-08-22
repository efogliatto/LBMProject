#ifndef LIANGCOLLISION_H
#define LIANGCOLLISION_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <liangEquilibrium.h>

void liangCollision(struct twoPhasesFields* fields, const struct solverInfo* info);

#endif // LIANGCOLLISION_H
