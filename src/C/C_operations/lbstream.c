#include <lbstream.h>

void lbstream( struct latticeMesh* mesh, struct lbeField* field ) {

    unsigned int id, k;

    
    // Copy all values to swap

    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

    	// Move over velocities
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    field->swap[id][k] = field->value[id][k];
	    
    	}

    }


    // Copy only neighbours to swap
    
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    int neighId = mesh->nb[id][k];

	    if( neighId != -1 ) {

		field->swap[id][k] = field->value[neighId][k];

	    }
    
	}

    }



    // Copy back from swap
    
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

	// Move over velocities
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    field->value[id][k] = field->swap[id][k];
	    
	}

    }



    
    // Sync fields
    syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q );
    
}
