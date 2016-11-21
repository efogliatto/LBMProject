#include <updateBoundaryVel.h>
#include <interactionForce.h>


void updateBoundaryVel( struct liModelInfo* info, struct bdInfo* bdElements, double** field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb ) {

    
    unsigned int bndId, i, j, k;

    // Interaction force
    double F[3];    

    
    // Move over boundaries
    for( bndId = 0 ; bndId < bdElements->_nb ; bndId++ ) {

	
	// Move over boundary elements
	for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	    
	    // Boundary element id
	    int id = bdElements->_idx[bndId][i];


	    // Compute interaction force
	    interactionForce( info, F, mfields->rho, nb, mfields->T[id], id );

	    // Initialize velocities
	    for(k = 0 ; k < 3 ; k++) {
		mfields->U[id][k] = 0;
	    }	
	


	    // Move over velocity components
	    for( j = 0 ; j < 3 ; j++ ) {

		// Move over model velocities
		for(k = 0 ; k < lattice->Q ; k++) {

		    mfields->U[id][j] += info->lattice.vel[k][j] * field[id][k] * lattice->c;
		    
		}
	    
	    }


	    // Add interaction force and divide by density
	    for( j = 0 ; j < 3 ; j++ ) {

		mfields->U[id][j] = ( mfields->U[id][j]   +   F[j] * info->time.tstep * 0.5  ) / mfields->rho[id];

	    }

	
       
	}


    }

}
