#include <temperatureCollision.h>
#include <liEquilibrium.h>
#include <stdlib.h>
#include <syncPdfField.h>
#include <interactionForce.h>
#include <p_eos.h>


void temperatureCollision( struct liModelInfo* info, double* T, double* rho, double** v, int** nb, double** g ) {

    // Indices
    unsigned int id, k, j;

    // Dot product for correction term
    double kappa, dot, M, phi;

    // Interaction force
    double F[3];

    
    // Partial distributions
    double* f_eq = (double*)malloc( info->lattice.Q * sizeof(double) );


    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Compute momentum equilibrium
	liEquilibrium(info, rho[id], v[id], f_eq);

	
	// Collide g
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    
	    // Interaction force
	    interactionForce( info, F, rho, nb, T, id);

	    
	    // Correction term (force)
	    kappa = ( 1 - 0.5 / info->fields.tau_T) * info->lattice.omega[k] * info->fields._Cv * T[id] / info->lattice.cs2;
	    
	    dot = 0;
	    for( j = 0 ; j < 3 ; j++) {
	    	dot += info->lattice.c * info->lattice.vel[k][j] * F[j];
	    }

	    M = kappa * dot;


	    

	    // Compresion work
	    
	    dot = 0;
	    for( j = 0 ; j < 3 ; j++) {
	    	dot += info->lattice.c * info->lattice.vel[k][j] * v[id][j];
	    }

	    phi = -T[id] * (p_eos(info, rho[id], T[id]*1.1) - p_eos(info, rho[id], T[id]*0.9)) / ( 2 * T[id]);


	    M = M - phi * info->lattice.omega[k] * dot / (info->fields.tau_T * info->time.tstep * info->lattice.cs2);


	    
	    
	    // Collision
	    g[id][k] = g[id][k]  -
		       (  g[id][k]  -  info->fields._Cv * T[id] * f_eq[k]  ) / info->fields.tau_T   +
		       info->time.tstep * M;

	    
	}


    }


    // Deallocate memory
    free(f_eq);


    // Synchronize field
    syncPdfField( &info->parallel, g, info->lattice.Q );

}
