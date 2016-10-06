#ifndef WRITEVTKFILE_H
#define WRITEVTKFILE_H

#include <mpiInfo.h>
#include <vtkInfo.h>
#include <timeInfo.h>

void writeVTKFile( struct vtkInfo* vtk, struct mpiInfo* parallel, struct timeInfo* time );


#endif // WRITEVTKFILE_H
