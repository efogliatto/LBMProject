#include <scalarFieldLaplacian.h>

double scalarFieldLaplacian( struct twoPhasesFields* fields, struct solverInfo* info, double* fld, int id ) {

    double lap = 0;

    unsigned int k;


    // Move over velocities
    for( k = 0 ; k < info->lattice.Q ; k++ ) {

	int nbId = fields->nb[id][k];
	
	if( nbId != -1 ) {

	    lap += 2 * info->lattice.omega[k] * ( fld[nbId] - fld[id] );
	    
	}

    }


    lap = lap / ( info->lattice.cs2 * info->time.tstep * info->time.tstep);
    
    return lap;
    
}
