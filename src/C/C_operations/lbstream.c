#include <lbstream.h>

void lbstream( c_scalar** fld, c_scalar** swp, int** nb, struct latticeInfo* lattice, struct mpiInfo* parallel ) {

    unsigned int id, k;

    
    // Copy all values to swap

    // Move over points
    for( id = 0 ; id < lattice->nlocal ; id++ ) {

    	// Move over velocities
    	for( k = 0 ; k < lattice->Q ; k++ ) {

    	    swp[id][k] = fld[id][k];
	    
    	}

    }


    // Copy only neighbours to swap
    
    // Move over points
    for( id = 0 ; id < lattice->nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    int neighId = nb[id][k];

	    if( neighId != -1 ) {

		swp[id][k] = fld[neighId][k];

	    }

	    else {

		swp[id][k] = fld[id][ lattice->reverse[k] ];
		
	    }
	    
	}

    }



    // Copy back from swap
    
    // Move over points
    for( id = 0 ; id < lattice->nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    fld[id][k] = swp[id][k];
	    
	}

    }



    
    // Sync fields
    syncPdfField( parallel, fld, lattice->Q );
    
}
