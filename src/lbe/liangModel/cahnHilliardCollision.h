#ifndef CAHNHILLIARDCOLLISION_H
#define CAHNHILLIARDCOLLISION_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <cahnHilliardEquilibrium.h>
#include <syncPdfField.h>

void cahnHilliardCollision(struct twoPhasesFields* fields, struct solverInfo* info);

#endif // CAHNHILLIARDCOLLISION_H
