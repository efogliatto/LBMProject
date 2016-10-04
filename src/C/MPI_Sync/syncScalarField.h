#ifndef SYNCSCALARFIELD_H
#define SYNCSCALARFIELD_H

#include <mpiInfo.h>
#include <twoPhasesFields.h>
#include <mpi.h>

void syncScalarField( struct mpiInfo* info, c_scalar* fld );

#endif // SYNCSCALARFIELD_H
