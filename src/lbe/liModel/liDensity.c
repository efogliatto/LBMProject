#include <liDensity.h>

void liDensity( struct liModelInfo* info, double* rho, double** f ) {

    unsigned int i, k;
    
    // Move over points
    for( i = 0 ; i < info->lattice.nlocal ; i++ ) {

	rho[i] = 0;
	
	// Move over velocities
	for(k = 0 ; k < info->lattice.Q ; k++) {

	    rho[i] += f[i][k];

	}

    }
	
}
