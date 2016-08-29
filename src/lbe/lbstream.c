#include <lbstream.h>

void lbstream( struct twoPhasesFields* fields, struct solverInfo* info, double** fld ) {

    unsigned int id, k;


    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

    	// Move over velocities
    	for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	    fields->swp[id][k] = fld[id][k];
	    
    	}

    }
    
    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    int neighId = fields->nb[id][k];

	    if( neighId != -1 ) {

		fields->swp[id][k] = fld[neighId][k];

	    }
	    
	}

    }



    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    fld[id][k] = fields->swp[id][k];
	    
	}

    }


    // Sync fields
    syncPdfField( info, fld, info->lattice.Q );
    
}
