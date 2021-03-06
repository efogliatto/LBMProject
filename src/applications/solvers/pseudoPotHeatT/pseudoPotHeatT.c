#include <stdio.h>
#include <pseudoPotCollision.h>
#include <pseudoPotTemperature.h>
#include <temperatureCollision.h>

#include <timeOptions.h>
#include <syncScalarField.h>
#include <syncPdfField.h>
#include <lbstream.h>
#include <writeScalarField.h>
#include <writeVectorField.h>
#include <writePdfField.h>
#include <readLiModelInfo.h>
#include <readNeighbours.h>
#include <pseudoPotVelocity.h>
#include <liDensity.h>
#include <readVTKInfo.h>

#include <writeVTKFile.h>
#include <writeVTKExtra.h>
#include <writeScalarToVTK.h>
#include <writeVectorToVTK.h>
#include <writePdfToVTK.h>

#include <liEquilibrium.h>

#include <readBoundaryElements.h>
#include <readBoundaryConditions.h>

#include <updateBC.h>
#include <updateBoundaryT.h>
#include <updateBoundaryDens.h>
#include <updateBoundaryVel.h>

#include <string.h>

int main( int argc, char **argv ) {



    // Check for arguments
    unsigned int ht = 1;
    {
	unsigned int arg;
	for( arg = 0 ; arg < argc ; arg++) {

	    if ( strcmp("--noHeatTransfer", argv[arg]) == 0 ) {
		ht = 0;
	    }
	    
	}
    }


    int pid, world;
    
    // Initialize mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    MPI_Comm_size(MPI_COMM_WORLD,&world);
    
    if(pid == 0) {
	printf("                    \n");	
	printf("     o-----o-----o  \n");
	printf("     | -   |   - |  \n");
	printf("     |   - | -   |  \n");
	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver. Pseudopotential model\n");
	printf("     |   - | -   |  \n");
	printf("     | -   |   - |  \n");
	printf("     o-----o-----o  \n");
    }
	
    // Simulation properties
    struct liModelInfo info = readLiModelInfo( pid, world );

    // VTK properties
    struct vtkInfo vtk = readVTKInfo(&info.lattice, &info.parallel);
    

    // Neighbours indices
    int** nb = readNeighbours(&info.lattice, &info.parallel);
    if(pid == 0) { printf("\nReading neighbour indices\n"); }


    // Boundary elements
    struct bdInfo bdElements = readBoundaryElements( pid, info.lattice.d, info.lattice.Q );
    readBoundaryConditions( &bdElements );
    


    

    // Macroscopic fields
    struct macroFields mfields;

    mfields.Cv = info.fields._Cv;

    
    // Density
    mfields.rho = readScalarField("rho", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field rho\n");  }

    
    // Velocity
    mfields.U = readVectorField("U", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field U\n");  }

    
    // Temperature
    mfields.T = readScalarField("T", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field T\n");  }
    
    
    // Navier-Stokes field
    double** f   = readPdfField("f", &info.lattice, &info.parallel, &info.time);
    double** f_swp = readPdfField("f", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field f\n");  }
    

    // Temperature field
    double** g     = readPdfField("g", &info.lattice, &info.parallel, &info.time);
    double** g_swp = readPdfField("g", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field g\n\n\n");  }
    
    
    // Initial equilibrium distribution
    {

	unsigned int id, k;

	for( id = 0 ; id < info.lattice.nlocal ; id++ ) {

	    // f
	    liEquilibrium(&info, mfields.rho[id], mfields.U[id], f[id]);

	    // g
	    for( k = 0 ; k < info.lattice.Q ; k++ ) {

	    	g[id][k] = info.fields._Cv * mfields.T[id] * f[id][k];

	    }
	    
	    

	}
	
    }

    
   
    // Synchronize initial fields
    syncScalarField(&info.parallel, mfields.rho );
    syncScalarField(&info.parallel, mfields.T );
    syncPdfField(&info.parallel, mfields.U, 3 );
    syncPdfField(&info.parallel, f, info.lattice.Q );
    syncPdfField(&info.parallel, g, info.lattice.Q );





    
    
    // Advance in time. Collide, stream, update and write
    while( updateTime(&info.time) ) {
	
	
    	// Collide f (Navier-Stokes)
    	pseudoPotCollision( &info, mfields.T, mfields.rho, mfields.U, nb, f );

    	// Density
    	liDensity( &info, mfields.rho, f );
	
    	// Velocity
    	pseudoPotVelocity( &info, mfields.rho, mfields.U, f, nb, mfields.T  );


	

	if( ht != 0 ) {
	
	    // Collide g (Temperature)
	    temperatureCollision( &info, mfields.T, mfields.rho, mfields.U, nb, g );
	
	}

	
    	// Stream
	lbstream( f, f_swp, nb, &info.lattice, &info.parallel );
	lbstream( g, g_swp, nb, &info.lattice, &info.parallel );
	
	
	
    	// Update macroscopic fields

    	// Density
    	liDensity( &info, mfields.rho, f );
	
    	// Velocity
    	pseudoPotVelocity( &info, mfields.rho, mfields.U, f, nb, mfields.T  );

	if( ht != 0 ) {
	
	    // Temperature
	    pseudoPotTemperature( &info, &mfields, g );

	}


	// Apply boundary conditions
	updateBC( &bdElements, nb, f, "f", &info.lattice, &mfields );
	if( ht != 0 ) { updateBC( &bdElements, nb, g, "g", &info.lattice, &mfields );  }

	// Update macroscopic fields only at boundary
	updateBoundaryDens( &bdElements, f, &info.lattice, &mfields );
	updateBoundaryVel( &info, &bdElements, f, &info.lattice, &mfields, nb );
	if( ht != 0 ) { updateBoundaryT( &bdElements, g, &info.lattice, &mfields ); }



	// Sync fields
	syncScalarField(&info.parallel, mfields.rho );
	syncScalarField(&info.parallel, mfields.T );
	syncPdfField(&info.parallel, mfields.U, 3 );
	syncPdfField(&info.parallel, f, info.lattice.Q );
	syncPdfField(&info.parallel, g, info.lattice.Q );
	

	
    	// Write fields
    	if( writeFlag(&info.time) ) {
	    
    	    if(pid == 0) {
    		printf("Time = %.2f (%d)\n", (double)info.time.current * info.time.tstep, info.time.current);
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&info.time) );
    	    }
	    
	    // VTK files 
	    writeVTKFile(&vtk, &info.parallel, &info.lattice, &info.time);
	    
	    writeScalarToVTK("rho", mfields.rho, &info.lattice, &info.parallel, &info.time);

	    writeScalarToVTK("T", mfields.T, &info.lattice, &info.parallel, &info.time);	    

	    writeVectorToVTK("U", mfields.U, &info.lattice, &info.parallel, &info.time);

	    writePdfToVTK("f", f, &info.lattice, &info.parallel, &info.time);

	    writePdfToVTK("g", g, &info.lattice, &info.parallel, &info.time);

	    writeVTKExtra(&vtk, &info.parallel, &info.time);
	    
    	}
	

    }


    
    // Print info
    if(pid == 0) {
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&info.time) );
    }


    MPI_Finalize();
    
    return 0;
    
}
