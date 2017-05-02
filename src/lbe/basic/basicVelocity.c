#include <basicVelocity.h>
#include <syncPdfField.h>

void basicVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int id, j, k;
   
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {
	
	// Initialize velocities
	for(k = 0 ; k < 3 ; k++) {
	    mfields->U[id][k] = 0;
	}	
	
	// Move over velocity components
	for( j = 0 ; j < 3 ; j++ ) {

	    // Move over model velocities
	    for(k = 0 ; k < mesh->lattice.Q ; k++) {

		mfields->U[id][j] += mesh->lattice.vel[k][j] * field->value[id][k] * mesh->lattice.c;
		    
	    }
	    
	}


	// Add interaction force and divide by density
	for( j = 0 ; j < 3 ; j++ ) {

	    mfields->U[id][j] = mfields->U[id][j] / mfields->rho[id];

	}
	

    }


    // Synchronize field
    syncPdfField( &mesh->parallel, mfields->U, 3 );
    
}
