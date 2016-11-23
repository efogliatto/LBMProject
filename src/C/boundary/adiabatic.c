#include <adiabatic.h>
#include <stdio.h>

// Use f_i^{eq} = Cv * T * rho * w_i * (1 + (Ci * U)/Cs2 + (Ci * U)^2/2Cs4 - U^2/sCs2)
double f_eq( double w, double rho, double U[3], int* ei, double cs2, double c );


// Uses "value" as lattice direction. Uses this value as boundary temperature

void adiabatic( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice, struct macroFields* mfields, int fid ) {

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
	    field[id][k] = field[nid][k];

	    
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




/* double f_eq_( double w, double rho, double U[3], int* ei, double cs2, double c ) { */

/*     double dot1 = c*ei[0]*U[0] + c*ei[1]*U[1] + c*ei[2]*U[2]; */
/*     double dot2 = U[0]*U[0] + U[1]*U[1] + U[2]*U[2]; */
    
/*     return w * rho * (1 + dot1/cs2 + dot1*dot1/(2*cs2*cs2) - dot2*0.5/cs2); */
    
/* } */
