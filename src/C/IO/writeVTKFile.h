#ifndef WRITEVTKFILE_H
#define WRITEVTKFILE_H

#include <mpiInfo.h>
#include <vtkInfo.h>
#include <timeInfo.h>
#include <latticeInfo.h>

void writeVTKFile( struct vtkInfo* vtk, struct mpiInfo* parallel, struct latticeInfo* lattice, struct timeInfo* time );


#endif // WRITEVTKFILE_H
