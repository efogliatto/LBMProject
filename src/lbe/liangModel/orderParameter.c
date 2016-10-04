#include <orderParameter.h>
#include <syncScalarField.h>

void orderParameter( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* fld ) {

    unsigned int id, k;

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	c_scalar ph = 0;
	
	// Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    ph += fields->h[id][k];

	}

	fld[id] = ph;

    }

    // Sync field
    syncScalarField( &info->parallel, fld );
    
}
