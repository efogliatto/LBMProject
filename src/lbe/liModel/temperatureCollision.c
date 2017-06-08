#include <temperatureCollision.h>
#include <lbgkTEquilibrium.h>
#include <lbgkEquilibrium.h>
#include <stdlib.h>
#include <syncPdfField.h>
#include <totalForce.h>
#include <p_eos.h>

#include <updateTau.h>

void temperatureCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    unsigned int id, k, j;

    // Dot product for correction term
    double kappa, dot, M;//, phi;

    // Interaction force
    double F[3];

    
    // Partial distributions
    double* f_eq = (double*)malloc( mesh->lattice.Q * sizeof(double) );


    
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {


	// Update thermal conductivity value (stored in field.tau)
	/* updateTau(field, mfields->rho[id], mesh->lattice.Q); */
	

	// Update real tau
	field->tau = 0.5 + field->lambda / (mesh->lattice.cs2 * mfields->rho[id] * mfields->Cv);

	
	// Compute momentum equilibrium
	/* lbgkTEquilibrium(&mesh->lattice, mfields->rho[id], mfields->U[id], f_eq); */
	lbgkEquilibrium(&mesh->lattice, mfields->rho[id], mfields->U[id], f_eq);	

	// Interaction force
	/* interactionForce( mesh, F, mfields->rho, mfields->T, id); */
	totalForce( mesh, F, mfields->rho, mfields->T, id);


	/* // Parameter for compression work */
	/* phi = -mfields->T[id] * (p_eos(&mesh->EOS, mfields->rho[id], mfields->T[id]*1.1) - p_eos(&mesh->EOS, mfields->rho[id], mfields->T[id]*0.9)) / ( 2 * mfields->T[id]); */



	
	// Collide g
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {


	    M = 0;
	    
	    // Correction term (force)
	    kappa = ( 1 - 0.5 / field->tau) * mesh->lattice.omega[k] * mfields->Cv * mfields->T[id] / mesh->lattice.cs2;
	    
	    dot = 0;
	    for( j = 0 ; j < 3 ; j++) {
	    	dot += mesh->lattice.c * mesh->lattice.vel[k][j] * F[j];
	    }

	    M = kappa * dot;


	    

	    /* // Compresion work */
	    
	    /* dot = 0; */
	    /* for( j = 0 ; j < 3 ; j++) { */
	    /* 	dot += mesh->lattice.c * mesh->lattice.vel[k][j] * mfields->U[id][j]; */
	    /* } */

	    /* M = M - phi * mesh->lattice.omega[k] * dot / (field->tau * mesh->time.tstep * mesh->lattice.cs2); */


	    
	    
	    // Collision
	    field->value[id][k] = field->value[id][k]  -
		       (  field->value[id][k]  -  mfields->Cv * mfields->T[id] * f_eq[k]  ) / field->tau   +
		        M;

	    
	}


    }


    // Deallocate memory
    free(f_eq);


    // Synchronize field
    syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q );

}
