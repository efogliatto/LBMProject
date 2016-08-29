#ifndef SYNCPDFFIELD_H
#define SYNCPDFFIELD_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <mpi.h>

void syncPdfField( const struct solverInfo* info, double** fld, int sz );

#endif // SYNCPDFFIELD_H
