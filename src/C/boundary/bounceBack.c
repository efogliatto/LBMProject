#include <bounceBack.h>

void bounceBack( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice ) {

    unsigned int i, k;

    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	int id = bdElements->_idx[bndId][i];
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    if ( nb[id][k] == -1 ) {

		field[id][k] = field[id][lattice->reverse[k]];

	    }

	}

    }

}
