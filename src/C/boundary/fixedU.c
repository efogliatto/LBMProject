#include <fixedU.h>
#include <stdlib.h>
#include <stdio.h>
#include <lbgkEquilibrium_id.h>


void fixedU( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId ) {

    
    unsigned int i, k;

    
    // Velocity at boundary
    double Uw[3];
    Uw[0] = bdElements->_value[fid][bndId][0];
    Uw[1] = bdElements->_value[fid][bndId][1];
    Uw[2] = bdElements->_value[fid][bndId][2];
    
    
    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	
	// Boundary element id
	int id = bdElements->_idx[bndId][i];
	
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {


	    if ( nb[id][k] == -1 ) {


		// Need density and velocity at neighbour (reverse) node
		int nbid = nb[id][ lattice->reverse[k] ];

		if( nbid != -1 ) {


		    // Compute equilibrium according to model
		    switch(field->colId) {

		    // MRT Li
		    case 0: {
			field->value[id][k] = lbgkEquilibrium_id(lattice, mfields->rho[nbid], Uw, k)
			    + field->value[nbid][k]
			    - lbgkEquilibrium_id(lattice, mfields->rho[nbid], mfields->U[nbid], k);
			break;
		    }

		    // SRT Li
		    case 1: {
			field->value[id][k] = lbgkEquilibrium_id(lattice, mfields->rho[nbid], Uw, k)
			    + field->value[nbid][k]
			    - lbgkEquilibrium_id(lattice, mfields->rho[nbid], mfields->U[nbid], k);
			break;
		    }			

		    default:
			printf("\n\n\n[ERROR]  Unable to update U for field %s\n\n\n",field->name);
			exit(1);
			break;


		    }




		}
		

	    }

	}



	
	

    }

}
