#include <fixedT.h>

// Use f_i^{eq} = Cv * T * rho * w_i * (1 + (Ci * U)/Cs2 + (Ci * U)^2/2Cs4 - U^2/sCs2)
double f_eq( double w, double rho, double U[3], int* ei, double cs2, double c );




void fixedT( struct bdInfo* bdElements, int** nb, double** field, int bndId, struct latticeInfo* lattice, struct macroFields* mfields, int fid ) {

    
    unsigned int i, k;
    

    // Move over boundary elements
    for( i = 0 ; i < bdElements->_nbel[bndId] ; i++ ) {

	int id = bdElements->_idx[bndId][i];
	
	// Move over lattice velocities
	for( k = 0 ; k < lattice->Q ; k++ ) {

	    if ( nb[id][k] == -1 ) {


		// Need density and velocity at neighbour (reverse) node
		int nbid = nb[id][ lattice->reverse[k] ];
	
		// Momentum equilibrium at neighbour
		double f_eq_nb = f_eq(lattice->omega[k], mfields->rho[nbid], mfields->U[nbid], lattice->vel[k], lattice->cs2, lattice->c);

		// Equilibrium at neighbour with patch T
		double eq_bnd = mfields->Cv * bdElements->_value[fid][bndId][0] * f_eq_nb; 

		// Equilibrium at neighbour with local T
		double eq_nb  = mfields->Cv * mfields->T[nbid] * f_eq_nb;



		// Update distribution
		field[id][k] = eq_bnd + (field[nbid][k] - eq_nb);
		

	    }

	}

    }

}




double f_eq( double w, double rho, double U[3], int* ei, double cs2, double c ) {

    double dot1 = c*ei[0]*U[0] + c*ei[1]*U[1] + c*ei[2]*U[2];
    double dot2 = U[0]*U[0] + U[1]*U[1] + U[2]*U[2];
    
    return w * rho * (1 + dot1/cs2 + dot1*dot1/(2*cs2*cs2) - dot2*0.5/cs2);
    
}
