#include <lbgkEquilibrium.h>

double lbgkEquilibrium_id( struct latticeInfo* lattice, double rho, double v[3], unsigned int id) {

    unsigned int j;

    double alpha = 0,
	beta = 0;

    // Dot product
    for( j = 0 ; j < 3 ; j++ ) {

	alpha += lattice->vel[id][j] * v[j];

	beta += v[j] * v[j];

    }

    alpha = alpha * lattice->c;

    return rho * lattice->omega[id] * ( 1 + alpha/lattice->cs2   +   0.5 * alpha * alpha / (lattice->cs2*lattice->cs2)  -  0.5 * beta / lattice->cs2 );

}
