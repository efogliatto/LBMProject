#include <orderParameter.h>

void orderParameter( struct twoPhasesFields* fields, struct solverInfo* info, double* fld ) {

    unsigned int id, k;

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	double ph = 0;
	
	// Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    ph += fields->h[id][k];

	}

	fields->phi[id] = ph;

    }
    
}
