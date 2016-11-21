#include <temperatureCollision.h>
#include <liEquilibrium.h>
#include <stdlib.h>
#include <syncPdfField.h>


void temperatureCollision( struct liModelInfo* info, double* T, double* rho, double** v, int** nb, double** g ) {

    // Indices
    unsigned int id, k;

    
    // Partial distributions
    double* f_eq = (double*)malloc( info->lattice.Q * sizeof(double) );


    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Compute momentum equilibrium
	liEquilibrium(info, rho[id], v[id], f_eq);

	
	// Collide g
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    g[id][k] = g[id][k]  -  info->fields.tau_T * (  g[id][k]  -  info->fields._Cv * T[id] * f_eq[k]  );

	}


    }


    // Deallocate memory
    free(f_eq);


    // Synchronize field
    syncPdfField( &info->parallel, g, info->lattice.Q );

}
