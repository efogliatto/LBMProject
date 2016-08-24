#include <gradient.h>
#include <stdlib.h>

const double* gradient( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id ) {

    double* grad = (double*)malloc( 3 * sizeof(double));

    unsigned int k;


    // Move over velocities
    for( k = 1 ; k < info->lattice.Q ; k++ ) {

    	int nbId = fields->nb[id][k];
	
    	if( nbId != -1 ) {

    	    grad[0] +=  -info->lattice.vel[k][0] * info->lattice.omega[k] * fld[nbId] * info->lattice.c;
	    grad[1] +=  -info->lattice.vel[k][1] * info->lattice.omega[k] * fld[nbId] * info->lattice.c;
	    grad[2] +=  -info->lattice.vel[k][2] * info->lattice.omega[k] * fld[nbId] * info->lattice.c;
	    
    	}

    }


    return grad;
    
}
