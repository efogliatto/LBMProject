#ifndef WRITEVTKEXTRA_H
#define WRITEVTKEXTRA_H

#include <mpiInfo.h>
#include <vtkInfo.h>
#include <timeInfo.h>

void writeVTKExtra( struct vtkInfo* vtk, struct mpiInfo* parallel, struct timeInfo* time );


#endif // WRITEVTKEXTRA_H
