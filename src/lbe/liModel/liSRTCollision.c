#include <liSRTCollision.h>
#include <syncPdfField.h>
#include <liEquilibrium.h>
#include <stdlib.h>
#include <totalForce.h>


void liSRTCollision( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb ) {

    // Indices
    unsigned int id, j, k;

    
    // Partial distributions
    double* feq   = (double*)malloc( info->lattice.Q * sizeof(double) );
    double* force = (double*)malloc( info->lattice.Q * sizeof(double) );

   
    // Total force
    double F[3];

    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {
	

	// Compute equilibrium
	liEquilibrium(info, mfields->rho[id], mfields->U[id], feq);

	
	// Total force
	totalForce( info, F, mfields->rho, nb, mfields->T, id);

	
	// Guo forcing scheme. Move over velocities
	for( k = 0 ; k < info->lattice.Q ; k++ ) {


	    // Dot product 1. (e_k - U) * F
	    double dot_1 = 0;	    
	    for( j = 0 ; j < info->lattice.d ; j++ ) {		
		dot_1 += (info->lattice.c * info->lattice.vel[k][j] - mfields->U[id][j]) * F[j];
	    }


	    // Dot product 2. e_k * U
	    double dot_2 = 0;	    
	    for( j = 0 ; j < info->lattice.d ; j++ ) {		
		dot_2 += info->lattice.c * info->lattice.vel[k][j] * mfields->U[id][j];
	    }

	    // Dot product 3. dot_2 * e_k * F
	    double dot_3 = 0;	    
	    for( j = 0 ; j < info->lattice.d ; j++ ) {		
		dot_3 += (dot_2 * info->lattice.c * info->lattice.vel[k][j] ) * F[j];
	    }

	    force[k] = (1 - 0.5 / field->tau) * info->lattice.omega[k] * (dot_1  + dot_3 / info->lattice.cs2) / info->lattice.cs2;
	    
	}


	
	// Collide field
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    field->value[id][k] = field->value[id][k]   -   (1/field->tau) * ( field->value[id][k] - feq[k] )   +   info->time.tstep * force[k];

	}

    }


    // Deallocate memory
    free(feq);



    // Synchronize field
    syncPdfField( &info->parallel, field->value, info->lattice.Q );


}
