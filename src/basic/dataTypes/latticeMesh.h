#ifndef LATTICEMESH_H
#define LATTICEMESH_H

#include <timeInfo.h>
#include <latticeInfo.h>
#include <mpiInfo.h>
#include <vtkInfo.h>


#define MPI_BUFF_SIZE 100



struct latticeMesh {

    // Time information
    struct timeInfo time;

    // DdQq information
    struct latticeInfo lattice;

    // Parallel structure
    struct mpiInfo parallel;

    // Neighbour indexing
    int** nb;

    // VTK properties
    struct vtkInfo vtk;
};



#endif // LATTICEMESH_H
