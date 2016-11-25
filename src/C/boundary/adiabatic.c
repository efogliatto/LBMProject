#include <adiabatic.h>
#include <stdio.h>
#include <lbgkEquilibrium.h>


// Uses "value" as lattice direction. Uses this value as boundary temperature
void adiabatic( struct bdInfo* bdElements, struct lbeField* field, struct latticeInfo* lattice, struct macroFields* mfields, int** nb, int fid, int bndId ) {

    // Indices
    unsigned int i, k;

    /* // Temperature at wall */
    /* double Tw; */

    // Boundary normal
    uint normal = (uint)bdElements->_value[fid][bndId][0];

    
    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	
	// Boundary element id
	int id = bdElements->_idx[bndId][i];

	// Neighbour id in normal direction
	uint nid = nb[id][normal];




	/* // Wall temperature */
	/* Tw = mfields->T[nid]; */
	
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {


	    // Simple copy
	    field->value[id][k] = field->value[nid][k];

	    
	    /* if ( nb[id][k] == -1 ) { */


	    /* 	// Need density and velocity at neighbour (reverse) node */
	    /* 	int nbid = nb[id][ lattice->reverse[k] ]; */

	    /* 	if( nbid != -1 ) { */

	    /* 	    // Momentum equilibrium at neighbour */
	    /* 	    double f_eq_nb = f_eq(lattice->omega[k], mfields->rho[nbid], mfields->U[nbid], lattice->vel[k], lattice->cs2, lattice->c); */

	    /* 	    // Equilibrium at neighbour with patch T */
	    /* 	    double eq_bnd = mfields->Cv * Tw * f_eq_nb; */
		    
	    /* 	    // Equilibrium at neighbour with local T */
	    /* 	    double eq_nb  = mfields->Cv * mfields->T[nbid] * f_eq_nb; */


	    /* 	    // Update distribution */
	    /* 	    field[id][k] = eq_bnd + (field[nbid][k] - eq_nb); */
		    
	    /* 	} */
		

	    /* } */


	    
	}


	

    }

}
