#include <bounceBack.h>
#include <stdio.h>

void bounceBack( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, int** nb, int bndId ) {

    unsigned int i, k;

    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	int id = bdElements->_idx[bndId][i];
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    if ( nb[id][k] == -1 ) {

		field->value[id][k] = field->value[id][lattice->reverse[k]];

	    }

	}

    }

}
