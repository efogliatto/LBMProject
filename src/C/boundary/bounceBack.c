#include <bounceBack.h>
#include <stdio.h>

void bounceBack( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, int** nb, int bndId, struct macroFields* mfields ) {

    unsigned int i, k, alpha;

    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	int id = bdElements->_idx[bndId][i];

	alpha = 0;
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    if ( nb[id][k] == -1 ) {

		field->value[id][k] = field->value[id][lattice->reverse[k]];

		if ( nb[id][lattice->reverse[k]] == -1 ) {

		    alpha = k;
		    
		}

	    }

	}




	// Apply corner correction
	if(alpha != 0) {


	    /* // Compute extrapolated density */
	    /* double rho = 0; */
	    /* int extra = 0; */

	    /* for( k = 0 ; k < lattice->Q ; k++ ) { */
		
	    /* 	if ( nb[id][k] != -1  ) { */

	    /* 	    rho += mfields->rho[ nb[id][k] ]; */
	    /* 	    extra++; */
		    
	    /* 	} */
		    
	    /* } */

	    /* rho = rho / extra; */


	    // Method 1. Complete density and velocity

	    /* // Compute partial sums */
	    /* double partial_1 = 0, partial_2 = 0; */

	    /* for( k = 0 ; k < lattice->Q ; k++ ) { */

	    /* 	if(  ( k != alpha )   &&   ( k != beta )  ) { */

	    /* 	    partial_1 += field->value[id][k]; */

	    /* 	    partial_2 += lattice->vel[k][0] * field->value[id][k]; */

	    /* 	} */

	    /* } */



	    /* // Update distribution values */
	    /* field->value[id][alpha] = 0.5 * ( -partial_2 / lattice->vel[alpha][0] + rho - partial_1  ); */
	    /* field->value[id][beta]  = rho - partial_1 - field->value[id][alpha]; */





	    /* // Method 2. Equilibrium values */

	    /* for( k = 0 ; k < lattice->Q ; k++ ) { */

	    /* 	field->value[id][k] = lattice->omega[k] * rho; */
		
	    /* } */
	    

	    
	}

	

    }

}
