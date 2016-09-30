#include <liVelocity.h>
#include <interactionForce.h>

void liVelocity( struct liModelInfo* info, double* rho, double** v, double** f, int** nb, double T ) {

    unsigned int i, j, k;

    // Interaction force
    double F[3];
    
    // Move over points
    for( i = 0 ; i < info->lattice.nlocal ; i++ ) {

	// Compute interaction force
	interactionForce( info, F, rho, nb, T, i );

	// Initialize velocities
	for(k = 0 ; k < 3 ; k++) {
	    v[i][k] = 0;
	}	
	
	// Move over model velocities
	for(k = 0 ; k < info->lattice.Q ; k++) {


	    
	}
	

    }
    
}
