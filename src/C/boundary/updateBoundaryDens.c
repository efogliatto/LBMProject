#include <updateBoundaryDens.h>


void updateBoundaryDens( struct bdInfo* bdElements, double** field, struct latticeInfo* lattice, struct macroFields* mfields ) {

    
    unsigned int bndId, i, k;
    

    // Move over boundaries
    for( bndId = 0 ; bndId < bdElements->_nb ; bndId++ ) {

	
	// Move over boundary elements
	for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	    
	    // Boundary element id
	    int id = bdElements->_idx[bndId][i];

	    double acum = 0;
	
	
	    // Move over lattice velocities
	    for( k = 0 ; k < lattice->Q ; k++ ) {

		acum += field[id][k];

	    }

	    mfields->rho[id] = acum;

	
       
	}


    }

}
