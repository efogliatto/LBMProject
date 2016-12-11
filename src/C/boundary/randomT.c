#include <randomT.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <lbgkEquilibrium.h>


void randomT( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId ) {

    
    unsigned int i, k;

    double* f_eq_nb = (double*)malloc( lattice->Q * sizeof(double) );
    double eq_bnd = 0;
    double eq_nb = 0;

    
    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	
	// Boundary element id
	int id = bdElements->_idx[bndId][i];


	// Number of neighbours without reverse
	unsigned int noneigh = 0;
	
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {


	    if ( nb[id][k] == -1 ) {


		// Need density and velocity at neighbour (reverse) node
		int nbid = nb[id][ lattice->reverse[k] ];

		if( nbid != -1 ) {
		    
		    double minp, maxp, r;

		    // Compute equilibrium according to model
		    switch(field->colId) {

		    case 2: {
			lbgkEquilibrium(lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb);

			minp = 1 - 1 / 100;
			maxp = 1 + 1 / 100;

			// Generate random numbers
			srand(time(NULL));

			r = (double)rand() / (double)RAND_MAX;

			eq_bnd = mfields->Cv * bdElements->_value[fid][bndId][0] * (minp + r * (maxp - minp)) * f_eq_nb[k];
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
		    /* printf("%d %d\n", id, nbid); */

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
