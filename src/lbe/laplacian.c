#include <laplacian.h>

const double laplacian( struct twoPhasesFields* fields, const struct solverInfo* info, double* fld, const int id ) {

    double lap = 0;

    unsigned int k;


    // Move over velocities
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

	int nbId = fields->nb[id][k];
	
	if( nbId != -1 ) {

	    lap += 2 * info->lattice.omega[k] * ( fld[nbId] - fld[id] );
	    
	}

    }


    return lap / ( info->lattice.cs2 * info->time.tstep * info->time.tstep);
    
}
