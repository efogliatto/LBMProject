#include <IOOptions.h>

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


#include <equilibrium.h>




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
    struct latticeMesh mesh = readLatticeMesh( pid, world );    
   
    

    // Macroscopic fields
    struct macroFields mfields;    
    mfields.Cv = readScalarEntry("properties/macroscopicProperties", "EOS/Cv");

    

    

    
    // Density
    mfields.rho = readScalarField("rho", &mesh.lattice, &mesh.parallel, &mesh.time);
    if(pid == 0) { printf("\nReading field rho\n");  }

    
    // Velocity
    mfields.U = readVectorField("U", &mesh.lattice, &mesh.parallel, &mesh.time);
    if(pid == 0) { printf("\nReading field U\n");  }

    
    // Temperature
    mfields.T = readScalarField("T", &mesh.lattice, &mesh.parallel, &mesh.time);
    if(pid == 0) { printf("\nReading field T\n");  }


    


    // LBE fields

    // Navier-Stokes field
    struct lbeField f = readLbeField("f", &mesh.lattice, &mesh.parallel, &mesh.time);
    
    // Energy field
    struct lbeField g = readLbeField("g", &mesh.lattice, &mesh.parallel, &mesh.time);
    

    // Initial equilibrium distribution
    {

    	unsigned int id;

    	for( id = 0 ; id < mesh.lattice.nlocal ; id++ ) {

    	    // f
    	    equilibrium(&mesh, &mfields, &f, id);

    	    // g
    	    equilibrium(&mesh, &mfields, &g, id);

    	}
	
    }

    
   
    // Synchronize initial fields
    syncScalarField(&mesh.parallel, mfields.rho );
    syncScalarField(&mesh.parallel, mfields.T );
    syncPdfField(&mesh.parallel, mfields.U, 3 );
    syncPdfField(&mesh.parallel, f.value, mesh.lattice.Q );
    syncPdfField(&mesh.parallel, g.value, mesh.lattice.Q );

    if(pid == 0){printf("\n\n");}








    
    // Advance in time. Collide, stream, update and write
    while( updateTime(&mesh.time) ) {
	
    	// Collide f (Navier-Stokes)
    	if( frozen != 0 ) {  collision( &mesh, &mfields, &f );  }
	

    	// Collide g (Temperature)
    	if( ht != 0 ) {

    	    // Update macroscopic density
    	    macroDensity( &mesh, &mfields, &f );
		
    	    // Update macroscopic velocity
    	    macroVelocity( &mesh, &mfields, &f );

	    collision( &mesh, &mfields, &g );

	}



	
    	// Stream f
    	if( frozen != 0 ) {  lbstream( &mesh, &f );  }

    	// Stream g
    	if( ht != 0 ) {  lbstream( &mesh, &g );  }

	

	
    	if( frozen != 0 ) {
	    
    	    // Update macroscopic density
    	    macroDensity( &mesh, &mfields, &f );
		
    	    // Update macroscopic velocity
    	    macroVelocity( &mesh, &mfields, &f );

    	}
	
    	// Update macroscopic temperature
    	if( ht != 0 ) {	    macroTemperature( &mesh, &mfields, &g );    }

	

	
    	// Apply boundary conditions
    	if( frozen != 0 ) {  updateBoundaries( &mesh, &mfields, &f );  }
    	if( ht != 0 )     {  updateBoundaries( &mesh, &mfields, &g );  }

    	// Update macro values at boundary elements
    	if( frozen != 0 ) {  updateBoundaryElements( &mesh, &mfields, &f );  }
    	if( ht != 0 )     {  updateBoundaryElements( &mesh, &mfields, &g );	}




    	// Sync fields
    	syncScalarField(&mesh.parallel, mfields.rho );
    	syncScalarField(&mesh.parallel, mfields.T );
    	syncPdfField(&mesh.parallel, mfields.U, 3 );
    	syncPdfField(&mesh.parallel, f.value, mesh.lattice.Q );
    	syncPdfField(&mesh.parallel, g.value, mesh.lattice.Q );
	

	
    	// Write fields
    	if( writeFlag(&mesh.time) ) {
	    
    	    if(pid == 0) {
    		printf("Time = %.2f (%d)\n", (double)mesh.time.current * mesh.time.tstep, mesh.time.current);
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&mesh.time) );
    	    }
	    
    	    // VTK files
    	    writeVTKFile(&mesh.vtk, &mesh.parallel, &mesh.lattice, &mesh.time);
	    
    	    writeScalarToVTK("rho", mfields.rho, &mesh.lattice, &mesh.parallel, &mesh.time);

    	    writeScalarToVTK("T", mfields.T, &mesh.lattice, &mesh.parallel, &mesh.time);

    	    writeVectorToVTK("U", mfields.U, &mesh.lattice, &mesh.parallel, &mesh.time);

    	    writePdfToVTK("f", f.value, &mesh.lattice, &mesh.parallel, &mesh.time);

    	    writePdfToVTK("g", g.value, &mesh.lattice, &mesh.parallel, &mesh.time);

    	    writeVTKExtra(&mesh.vtk, &mesh.parallel, &mesh.time);
	    
    	}
	

    }


    
    // Print info
    if(pid == 0) {
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&mesh.time) );
    }


    MPI_Finalize();
    
    return 0;
    
}
