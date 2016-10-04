#include <liEquilibrium.h>

void liEquilibrium( struct liModelInfo* info, double rho, double v[3], double* f ) {

    unsigned int k, j;

    // Move over velocities
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

	double alpha = 0,
	    beta = 0;

	// Dot product
	for( j = 0 ; j < 3 ; j++ ) {

	    alpha += info->lattice.vel[k][j] * v[j];

	    beta += v[j] * v[j];

	}

	alpha = alpha * info->lattice.c;

	f[k] = rho * info->lattice.omega[k] * ( 1 + alpha/info->lattice.cs2   +   0.5 * alpha * alpha / (info->lattice.cs2*info->lattice.cs2)  -  0.5 * beta / info->lattice.cs2 );
	

    }

}
