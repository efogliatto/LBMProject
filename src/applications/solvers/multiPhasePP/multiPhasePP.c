#include <readLbeField.h>
#include <collision.h>
#include <macroDensity.h>
#include <macroVelocity.h>
#include <macroTemperature.h>
#include <updateBoundaries.h>
#include <updateBoundaryElements.h>


#include <timeOptions.h>
#include <syncScalarField.h>
#include <syncPdfField.h>
#include <lbstream.h>
#include <writeScalarField.h>
#include <writeVectorField.h>
#include <writePdfField.h>
#include <readLiModelInfo.h>
#include <readNeighbours.h>
#include <readVTKInfo.h>

#include <writeVTKFile.h>
#include <writeVTKExtra.h>
#include <writeScalarToVTK.h>
#include <writeVectorToVTK.h>
#include <writePdfToVTK.h>

#include <equilibrium.h>

#include <readBoundaryElements.h>
#include <readBoundaryConditions.h>

#include <string.h>



int main( int argc, char **argv ) {



    // Check for arguments
    unsigned int ht = 1, frozen = 1;
    {
	unsigned int arg;
	for( arg = 0 ; arg < argc ; arg++) {

	    if ( strcmp("--noHeatTransfer", argv[arg]) == 0 ) {
		ht = 0;
	    }

	    else {

		if ( strcmp("--frozenFlow", argv[arg]) == 0 ) {
		    frozen = 0;
		}
		
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
	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver with heat transfer. Pseudopotential model\n");
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




    // LBE fields

    // Navier-Stokes field
    struct lbeField f = readLbeField("f", &info.lattice, &info.parallel, &info.time);
    
    // Energy field
    struct lbeField g = readLbeField("g", &info.lattice, &info.parallel, &info.time);
    

    // Initial equilibrium distribution
    {

    	unsigned int id;

    	for( id = 0 ; id < info.lattice.nlocal ; id++ ) {

    	    // f
    	    equilibrium(&info, &mfields, &f, id);

    	    // g
    	    equilibrium(&info, &mfields, &g, id);

    	}
	
    }

    
   
    // Synchronize initial fields
    syncScalarField(&info.parallel, mfields.rho );
    syncScalarField(&info.parallel, mfields.T );
    syncPdfField(&info.parallel, mfields.U, 3 );
    syncPdfField(&info.parallel, f.value, info.lattice.Q );
    syncPdfField(&info.parallel, g.value, info.lattice.Q );

    if(pid == 0){printf("\n\n");}








    
    // Advance in time. Collide, stream, update and write
    while( updateTime(&info.time) ) {
	

	if( frozen != 0 ) {

	    // Collide f (Navier-Stokes)
	    collision( &info, &mfields, &f, nb );

	    // Update macroscopic density
	    macroDensity( &info, &mfields, &f );
		
	    // Update macroscopic velocity
	    macroVelocity( &info, &mfields, &f, nb );

	}
	

	
	
	// Collide g (Temperature)
	if( ht != 0 ) {
	    collision( &info, &mfields, &g, nb );
	}


    	// Stream f
	if( frozen != 0 ) {
	    lbstream( f.value, f.swap, nb, &info.lattice, &info.parallel );
	}

    	// Stream g
	if( ht != 0 ) {
	    lbstream( g.value, g.swap, nb, &info.lattice, &info.parallel );
	}

	
	if( frozen != 0 ) {
	    
	    // Update macroscopic density
	    macroDensity( &info, &mfields, &f );
		
	    // Update macroscopic velocity
	    macroVelocity( &info, &mfields, &f, nb );

	}
	
	// Update macroscopic temperature
    	if( ht != 0 ) {
	    macroTemperature( &info, &mfields, &g );
    	}

	

    	// Apply boundary conditions
	if( frozen != 0 ) {
	    updateBoundaries( &bdElements, &f, &info.lattice, &mfields, nb );
	}
    	if( ht != 0 ) {
	    updateBoundaries( &bdElements, &g, &info.lattice, &mfields, nb );
	}

	if( frozen != 0 ) {
	    updateBoundaryElements( &bdElements, &f, &info, &mfields, nb );
	}
    	if( ht != 0 ) {
	    updateBoundaryElements( &bdElements, &g, &info, &mfields, nb );
	}




    	// Sync fields
    	syncScalarField(&info.parallel, mfields.rho );
    	syncScalarField(&info.parallel, mfields.T );
    	syncPdfField(&info.parallel, mfields.U, 3 );
    	syncPdfField(&info.parallel, f.value, info.lattice.Q );
    	syncPdfField(&info.parallel, g.value, info.lattice.Q );
	

	
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

    	    writePdfToVTK("f", f.value, &info.lattice, &info.parallel, &info.time);

    	    writePdfToVTK("g", g.value, &info.lattice, &info.parallel, &info.time);

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
