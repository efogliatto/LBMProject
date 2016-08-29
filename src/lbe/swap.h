#ifndef SWAP_H
#define SWAP_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <syncPdfField.h>

void swap( struct twoPhasesFields* fields, const struct solverInfo* info, double** fld );

#endif // SWAP_H
