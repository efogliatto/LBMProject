#ifndef SYNCPDFFIELD_H
#define SYNCPDFFIELD_H

#include <mpiInfo.h>
#include <twoPhasesFields.h>
#include <mpi.h>

void syncPdfField( struct mpiInfo* info, c_scalar** fld, int sz );

#endif // SYNCPDFFIELD_H
