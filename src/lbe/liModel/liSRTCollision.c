#include <liSRTCollision.h>
#include <syncPdfField.h>
#include <lbgkEquilibrium.h>
#include <stdlib.h>
#include <totalForce.h>
#include <updateTau.h>


void liSRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    // Indices
    unsigned int id, j, k;

    
    // Partial distributions
    double* feq   = (double*)malloc( mesh->lattice.Q * sizeof(double) );
    double* force = (double*)malloc( mesh->lattice.Q * sizeof(double) );

   
    // Total force
    double F[3];

    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {

	// Update tau value
	updateTau(field, mfields->rho[id], mesh->lattice.Q);	

	// Compute equilibrium
	lbgkEquilibrium(&mesh->lattice, mfields->rho[id], mfields->U[id], feq);

	
	// Total force
	totalForce( mesh, F, mfields->rho, mfields->T, id);

	
	// Guo forcing scheme. Move over velocities
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {


	    // Dot product 1. (e_k - U) * F
	    double dot_1 = 0;	    
	    for( j = 0 ; j < mesh->lattice.d ; j++ ) {		
		dot_1 += (mesh->lattice.c * mesh->lattice.vel[k][j] - mfields->U[id][j]) * F[j];
	    }


	    // Dot product 2. e_k * U
	    double dot_2 = 0;	    
	    for( j = 0 ; j < mesh->lattice.d ; j++ ) {		
		dot_2 += mesh->lattice.c * mesh->lattice.vel[k][j] * mfields->U[id][j];
	    }

	    // Dot product 3. dot_2 * e_k * F
	    double dot_3 = 0;	    
	    for( j = 0 ; j < mesh->lattice.d ; j++ ) {		
		dot_3 += (dot_2 * mesh->lattice.c * mesh->lattice.vel[k][j] ) * F[j];
	    }

	    force[k] = (1 - 0.5 / field->tau) * mesh->lattice.omega[k] * (dot_1  + dot_3 / mesh->lattice.cs2) / mesh->lattice.cs2;
	    
	}


	
	// Collide field
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    field->value[id][k] = field->value[id][k]   -   (1/field->tau) * ( field->value[id][k] - feq[k] )   +   mesh->time.tstep * force[k];

	}

    }


    // Deallocate memory
    free(feq);
    free(force);



    // Synchronize field
    syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q );


}
