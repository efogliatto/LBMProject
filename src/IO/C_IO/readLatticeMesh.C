// Read information for c-written solvers

#include <readLatticeMesh.h>
#include <readMPIInfo.h>
#include <readLatticeInfo.h>
#include <readTimeInfo.h>
#include <readVTKInfo.h>
#include <readNeighbours.h>
#include <readBoundaryElements.h>
#include <readBoundaryConditions.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct latticeMesh readLatticeMesh( int pid, int sz ) {

	struct latticeMesh mesh;

	
	// Time information
	mesh.time = readTimeInfo();

	// DdQq information
	mesh.lattice = readLatticeInfo(&mesh.time, pid);

	// MPI information
	mesh.parallel = readMPIInfo(pid, sz, mesh.lattice.nlocal);

	// VTK properties
	mesh.vtk = readVTKInfo(&mesh.lattice, &mesh.parallel);
    

	// Neighbours indices
	if(pid == 0) { printf("\nReading neighbour indices\n"); }
	mesh.nb = readNeighbours(&mesh.lattice, &mesh.parallel);


	// Boundary elements
	mesh.bdElements = readBoundaryElements( pid, mesh.lattice.d, mesh.lattice.Q );
	readBoundaryConditions( &mesh.bdElements );
    
       
    
	return mesh;
    
    }


#ifdef __cplusplus
}
#endif
