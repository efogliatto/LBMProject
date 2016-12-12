#include <adiabatic.h>
#include <stdio.h>
#include <lbgkTEquilibrium.h>
#include <stdlib.h>
#include <stdio.h>


// Uses "value" as lattice direction. Uses this value as boundary temperature
void adiabatic( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId ) {

    // Indices
    unsigned int i, k;

    // Temperature at wall
    double Tw;

    // Boundary normal
    uint normal = (uint)bdElements->_value[fid][bndId][0];

    // Auxiliar pdf values
    double* f_eq_nb = (double*)malloc( lattice->Q * sizeof(double) );
    double eq_bnd = 0;
    double eq_nb = 0;

    
    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	
	// Boundary element id
	int id = bdElements->_idx[bndId][i];

	// Neighbour id in normal direction
	uint nid = nb[id][normal];


	// Wall temperature
	Tw = mfields->T[nid];	


	// Number of neighbours without reverse
	unsigned int noneigh = 0;
	
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {


	    if ( nb[id][k] == -1 ) {


		// Need density and velocity at neighbour (reverse) node
		int nbid = nb[id][ lattice->reverse[k] ];

		if( nbid != -1 ) {


		    // Compute equilibrium according to model
		    switch(field->colId) {

		    case 2: {
			lbgkTEquilibrium(lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb);
			eq_bnd = mfields->Cv * Tw * f_eq_nb[k];
			eq_nb  = mfields->Cv * mfields->T[nbid] * f_eq_nb[k];
			break;
		    }

		    default:
			printf("\n\n\n[ERROR]  Unable to update T for field %s\n\n\n",field->name);
			exit(1);
			break;


		    }


		    // Update distribution
		    field->value[id][k] = eq_bnd + (field->value[nbid][k] - eq_nb);


		}


		else {

		    noneigh++;

		}
		

	    }

	}


	// Apply correction for corners
	if( noneigh != 0 ) {

	    
	}

    	

    }


    free(f_eq_nb);


}












/* // Uses "value" as lattice direction. Uses this value as boundary temperature */
/* void adiabatic( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId ) { */

/*     // Indices */
/*     unsigned int i, k; */


/*     // Boundary normal */
/*     uint normal = (uint)bdElements->_value[fid][bndId][0]; */

    
/*     // Move over boundary elements */
/*     for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) { */

	
/* 	// Boundary element id */
/* 	int id = bdElements->_idx[bndId][i]; */

/* 	// Neighbour id in normal direction */
/* 	uint nid = nb[id][normal]; */
	
/* 	// Move over lattice velocities */
/* 	for( k = 0 ; k < lattice->Q ; k++ ) { */

/* 	    // Simple copy */
/* 	    field->value[id][k] = field->value[nid][k]; */
	    
/* 	}	 */

/*     } */

/* } */
