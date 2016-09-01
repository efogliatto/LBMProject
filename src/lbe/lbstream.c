#include <lbstream.h>

void lbstream( struct twoPhasesFields* fields, struct solverInfo* info, double** fld ) {

    unsigned int id, k;

    
    // Copy all values to swap

    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

    	// Move over velocities
    	for( k = 0 ; k < info->lattice.Q ; k++ ) {

    	    fields->swp[id][k] = fld[id][k];
	    
    	}

    }


    // Copy only neighbours to swap
    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    int neighId = fields->nb[id][k];

	    if( neighId != -1 ) {

		fields->swp[id][k] = fld[neighId][k];

	    }

	    else {

		fields->swp[id][k] = fld[id][ info->lattice.reverse[k] ];
		
	    }
	    
	}

    }



    // Copy back from swap
    
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
