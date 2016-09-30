#ifndef SYNCPDFFIELD_H
#define SYNCPDFFIELD_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <mpi.h>

void syncPdfField( struct solverInfo* info, c_scalar** fld, int sz );

#endif // SYNCPDFFIELD_H
