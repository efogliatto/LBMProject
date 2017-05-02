#include <testEquilibrium.h>

void testEquilibrium( struct latticeInfo* lattice, struct EOSInfo* info, double rho, double v[3], double T, double* f ) {

    unsigned int k, j;

    // van der waals sound speed
    double cs2 = info->_M * info->_R * T / (info->_M - rho * info->_b)  -  2.0 * rho * info->_a / (info->_M * info->_M);
    cs2 = cs2 * cs2;

    // Move over velocities
    for( k = 0 ; k < lattice->Q ; k++ ) {

	double alpha = 0,
	    beta = 0;

	// Dot product
	for( j = 0 ; j < 3 ; j++ ) {

	    alpha += lattice->vel[k][j] * v[j];

	    beta += v[j] * v[j];

	}

	alpha = alpha * lattice->c;

	f[k] = rho * lattice->omega[k] * ( 1 + alpha/cs2   +   0.5 * alpha * alpha / (cs2*cs2)  -  0.5 * beta / cs2 );
	

    }

}
