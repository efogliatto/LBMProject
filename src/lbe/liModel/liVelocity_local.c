#include <liVelocity_local.h>
#include <totalForce.h>


void liVelocity_local( struct liModelInfo* info, double* rho, double** v, double** f, int** nb, double* T, unsigned int id ) {

    unsigned int j, k;

    // Interaction force
    double F[3];
 	
    // Compute interaction force
    totalForce( info, F, rho, nb, T, id );

	
    // Initialize velocities
    for(k = 0 ; k < 3 ; k++) {
	v[id][k] = 0;
    }	
	


    // Move over velocity components
    for( j = 0 ; j < info->lattice.d ; j++ ) {

	// Move over model velocities
	for(k = 0 ; k < info->lattice.Q ; k++) {

	    v[id][j] += info->lattice.vel[k][j] * f[id][k] * info->lattice.c;
		    
	}
	    
    }


    // Add interaction force and divide by density
    for( j = 0 ; j < 3 ; j++ ) {

	v[id][j] = ( v[id][j]   +   F[j] * info->time.tstep * 0.5  ) / rho[id];

    }
	
    
}
