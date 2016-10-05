#include <stdio.h>
#include <liCollision.h>
#include <timeOptions.h>
#include <syncScalarField.h>
#include <syncPdfField.h>
#include <lbstream.h>
#include <writeScalarField.h>
#include <writeVectorField.h>
#include <writePdfField.h>
#include <readLiModelInfo.h>
#include <readNeighbours.h>
#include <liVelocity.h>
#include <liDensity.h>
#include <liEquilibrium.h>

#include <potential.h>

int main( int argc, char **argv ) {

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
    

    // Neighbours indices
    int** nb = readNeighbours(&info.lattice, &info.parallel);
    if(pid == 0) { printf("\nReading neighbour indices\n"); }

    // Density
    double* rho = readScalarField("rho", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field rho\n");  }

    // Velocity
    double** U = readVectorField("U", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field U\n");  }

    // Navier-Stokes field
    double** f   = readPdfField("f", &info.lattice, &info.parallel, &info.time);
    double** swp = readPdfField("f", &info.lattice, &info.parallel, &info.time);
    if(pid == 0) { printf("\nReading field f\n\n\n");  }
    

    // Equilibrium distribution using rho and U
    {
    	unsigned int id;
    	for( id = 0 ; id < info.lattice.nlocal ; id++ ) {
    	    liEquilibrium(&info, rho[id], U[id], f[id]);
    	}
	
    }

    
    

    /* // Synchronize initial fields */
    /* syncScalarField(&info.parallel, rho ); */
    /* syncPdfField(&info.parallel, U, 3 ); */
    /* syncPdfField(&info.parallel, f, info.lattice.Q ); */


    
    // Advance in time. Collide, stream, update and write
    while( updateTime(&info.time) ) {


    	/* // Collide f (Navier-Stokes) */
    	/* liCollision( &info, info.fields._T, rho, U, nb, f ); */
	
    	/* // Stream */
	/* lbstream( f, swp, nb, &info.lattice, &info.parallel ); */


	
    	// Update macroscopic fields

    	// Density
    	liDensity( &info, rho, f );

	{
	    unsigned int id;
	    for( id = 0 ; id < info.lattice.nlocal ; id++ ) {
		printf("%f\n",potential(&info, rho[id], info.fields._T));
	    }
	
	}    	
	
    	/* // Velocity */
    	/* liVelocity( &info, rho, U, f, nb, info.fields._T  ); */
       


	
    	// Write fields
    	if( writeFlag(&info.time) ) {
	    
    	    if(pid == 0) {
    		printf("Time = %.2f (%d)\n", (double)info.time.current * info.time.tstep, info.time.current);
    		printf("Elapsed time = %.2f seconds\n\n", elapsed(&info.time) );
    	    }
	    
    	    // ScalarFields
    	    writeScalarField("rho", rho, &info.lattice, &info.parallel, &info.time);

    	    // Vector fields
    	    writeVectorField("U", U, &info.lattice, &info.parallel, &info.time);

    	    // Pdf fields
    	    writePdfField("f", f, &info.lattice, &info.parallel, &info.time);
	    
    	}
	

    }


    
    // Print info
    if(pid == 0) {
    	printf("\n  Finished in %.2f seconds \n\n", elapsed(&info.time) );
    }


    MPI_Finalize();
    
    return 0;
    
}