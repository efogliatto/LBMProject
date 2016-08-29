#include <stdio.h>
#include <twoPhasesFields.h>
#include <cahnHilliardCollision.h>
#include <liangCollision.h>
#include <timeOptions.h>
#include <density.h>
#include <pressureWithU.h>
#include <chemicalPotential.h>
#include <orderParameter.h>
#include <syncScalarField.h>
#include <syncPdfField.h>

int main( int argc, char **argv ) {

    int pid;
    
    // Initialize mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);

    if(pid == 0) {
	printf("     o-----o-----o  \n");
	printf("     | -   |   - |  \n");
	printf("     |   - | -   |  \n");
	printf("     o<----o---->o       Two Phases - Lattice-Boltzmann solver\n");
	printf("     |   - | -   |  \n");
	printf("     | -   |   - |  \n");
	printf("     o-----o-----o  \n");
    }
	
    // Simulation properties
    struct solverInfo info = readBasicInfo( pid );

    
    // Read Fields
    struct twoPhasesFields fields;

    // Neighbours indices
    fields.nb = readNeighbours(&info);
    if(pid == 0) { printf("\nReading neighbour indices\n"); }
    
    // Order parameter
    fields.phi     = readScalarField("phi", &info);
    fields.phi_old = readScalarField("phi", &info);
    if(pid == 0) { printf("\nReading field phi\n"); }

    // Chemical potential
    fields.muPhi = readScalarField("muPhi", &info);
    if(pid == 0) { printf("\nReading field muPhi\n"); }

    // Pressure
    fields.p = readScalarField("p", &info);
    if(pid == 0) { printf("\nReading field p\n"); }

    // Density
    fields.rho = readScalarField("rho", &info);
    if(pid == 0) { printf("\nReading field rho\n");  }

    // Velocity
    fields.U     = readVectorField("U", &info);
    fields.U_old = readVectorField("U", &info);
    if(pid == 0) { printf("\nReading field U\n");  }

    // Cahn-Hilliard field
    fields.h = readPdfField("h", &info);
    if(pid == 0) { printf("\nReading field h\n");  }

    // Navier-Stokes field
    fields.g = readPdfField("g", &info);
    fields.swp = readPdfField("g", &info);
    if(pid == 0) { printf("\nReading field g\n\n\n");  }
    


    // Synchronize initial fields
    syncScalarField(&info, fields.phi );
    syncScalarField(&info, fields.muPhi );
    syncScalarField(&info, fields.p );
    syncScalarField(&info, fields.rho );

    syncPdfField(&info, fields.U, 3 );
    syncPdfField(&info, fields.h, info.lattice.Q );
    syncPdfField(&info, fields.g, info.lattice.Q );


    
    // Advance in time. Collide, stream, update and write
    while( updateTime(&info) ) {
	
    	/* // Collide h */
    	/* cahnHilliardCollision(&fields, &info); */
	
    	/* // Collide g */
    	/* liangCollision(&fields, &info); */

	/* // Swap fields */
	/* swap( &fields, &info, fields.h ); */
	/* swap( &fields, &info, fields.g ); */
	

	/* // Update macroscopic fields */

	/* // Order parameter */
	/* orderParameter( &fields, &info, fields.phi );	 */
	
	/* // Chemical potential */
	/* chemicalPotential( &fields, &info, fields.muPhi );	 */
	
	/* // Density */
	/* density( &fields, &info, fields.rho ); */

	/* // Velocity */
	/* velocity( &fields, &info, fields.U ); */

	/* // Pressure */
	/* pressureWithU( &fields, &info, fields.p ); */

	/* // Old values */
	/* { */

	/*     unsigned int id, k; */

	/*     for( id = 0 ; id < info.lattice.nlocal ; id++ ) { */

	/* 	fields.phi_old[id] = fields.phi[id]; */
		
	/* 	for( k = 0 ; k < 3 ; k++ ) { */

	/* 	    fields.U_old[id][k] = fields.U[id][k]; */

	/* 	} */

	/*     } */
	    
	/* } */
	
	
    	// Write fields
    	if( writeFlag(&info) ) {
	    
	    if(pid == 0) {
		printf("Time = %.2f\n", info.time.current);
		printf("Elapsed time = %.2f seconds\n\n", elapsed(&info) );
	    }
	    
    	    // ScalarFields
    	    writeScalarField("phi", fields.phi, &info);
    	    writeScalarField("muPhi", fields.muPhi, &info);
    	    writeScalarField("rho", fields.rho, &info);
    	    writeScalarField("p", fields.p, &info);

    	    // Vector fields
    	    writeVectorField("U", fields.U, &info);

    	    // Pdf fields
    	    writePdfField("h", fields.h, &info);
    	    writePdfField("g", fields.g, &info);
	    
    	}

    }


    
    // Print info
    if(pid == 0) {
	printf("\n  Finished in %.2f seconds \n\n", elapsed(&info) );
    }


    MPI_Finalize();
    
    return 0;
    
}
