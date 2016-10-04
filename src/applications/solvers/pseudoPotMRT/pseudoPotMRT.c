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
    


    /* // Synchronize initial fields */
    /* syncScalarField(&info, rho ); */
    /* syncPdfField(&info, U, 3 ); */
    /* syncPdfField(&info, f, info.lattice.Q ); */


    
    /* // Advance in time. Collide, stream, update and write */
    /* while( updateTime(&info) ) { */


    /* 	// Collide h (Cahn-Hilliard) */
    /* 	cahnHilliardCollision(&fields, &info); */


	
    /* 	// Update macroscopic fields */

    /* 	// Order parameter */
    /* 	orderParameter( &fields, &info, fields.phi ); */
	
    /* 	// Chemical potential */
    /* 	chemicalPotential( &fields, &info, fields.muPhi ); */

    /* 	// Density */
    /* 	density( &fields, &info, fields.rho ); */
	
    /* 	// Velocity */
    /* 	velocity( &fields, &info, fields.U ); */

    /* 	// Pressure */
    /* 	pressureWithU( &fields, &info, fields.p ); */
	

	
	
    /* 	// Collide g (Navier - Stokes) */
    /* 	liangCollision(&fields, &info); */

	
    /* 	// Stream */
    /* 	lbstream( &fields, &info, fields.h ); */
    /* 	lbstream( &fields, &info, fields.g ); */



    /* 	// Old values */
    /* 	{ */

    /* 	    unsigned int id, k; */

    /* 	    for( id = 0 ; id < info.lattice.nlocal ; id++ ) { */

    /* 		fields.phi_old[id] = fields.phi[id]; */
		
    /* 		for( k = 0 ; k < 3 ; k++ ) { */

    /* 		    fields.U_old[id][k] = fields.U[id][k]; */

    /* 		} */

    /* 	    } */
	    
    /* 	} */
	
	
    /* 	// Update macroscopic fields */

    /* 	// Order parameter */
    /* 	orderParameter( &fields, &info, fields.phi ); */
	
    /* 	// Chemical potential */
    /* 	chemicalPotential( &fields, &info, fields.muPhi ); */

    /* 	// Velocity */
    /* 	velocity( &fields, &info, fields.U ); */

    /* 	// Pressure */
    /* 	pressureWithU( &fields, &info, fields.p ); */
	
    /* 	// Density */
    /* 	density( &fields, &info, fields.rho ); */



	
	
    /* 	// Write fields */
    /* 	if( writeFlag(&info) ) { */
	    
    /* 	    if(pid == 0) { */
    /* 		printf("Time = %.2f (%d)\n", (double)info.time.current * info.time.tstep, info.time.current); */
    /* 		printf("Elapsed time = %.2f seconds\n\n", elapsed(&info) ); */
    /* 	    } */
	    
    /* 	    // ScalarFields */
    /* 	    writeScalarField("phi", fields.phi, &info); */
    /* 	    writeScalarField("muPhi", fields.muPhi, &info); */
    /* 	    writeScalarField("rho", fields.rho, &info); */
    /* 	    writeScalarField("p", fields.p, &info); */

    /* 	    // Vector fields */
    /* 	    writeVectorField("U", fields.U, &info); */

    /* 	    // Pdf fields */
    /* 	    writePdfField("h", fields.h, &info); */
    /* 	    writePdfField("g", fields.g, &info); */
	    
    /* 	} */

    /* } */


    
    /* // Print info */
    /* if(pid == 0) { */
    /* 	printf("\n  Finished in %.2f seconds \n\n", elapsed(&info) ); */
    /* } */


    /* MPI_Finalize(); */
    
    return 0;
    
}
