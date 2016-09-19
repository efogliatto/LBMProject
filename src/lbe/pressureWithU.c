#include <pressureWithU.h>
#include <scalarFieldGradient.h>
#include <biasedGradient.h>
#include <syncScalarField.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void pressureWithU( struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* fld ) {

    unsigned int id, k;
    int scheme = -1;

    // Schemes
    char* dd[] = {"central", "biased"};
    for( k = 0 ; k < 2 ; k++ ) {
	if( strcmp(dd[k], info->lattice.dd) == 0 ) {
	    scheme = k;
	}
    }


    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Pdf reduction, excluding first element
	c_scalar red = 0;
	for( k = 1 ; k < info->lattice.Q ; k++ ) {

	    red += fields->g[id][k];

	}


	// Density gradient
	c_scalar* rhoGrad;
    
	switch( scheme ) {

	case 0:
	    rhoGrad = scalarFieldGradient( fields, info, fields->rho, id );
	    break;

	case 1:
	    rhoGrad = biasedGradient( fields->rho, fields->nb, fields->U, info->lattice.principal, info->lattice.size, id );
	    break;

	default:
	    if(info->parallel.pid == 0) { printf("[ERROR]  Unrecognized derivative scheme %s\n\n", info->lattice.dd); }
	    exit(1);
	    break;
	
	}


	// Dot product: U * grad(rho)
	c_scalar dot = fields->U[id][0] * rhoGrad[0]   +   fields->U[id][1] * rhoGrad[1]   +   fields->U[id][2] * rhoGrad[2];	

	
	// Equilibrium source term
	c_scalar Umag  = fields->U[id][0] * fields->U[id][0]  +  fields->U[id][1] * fields->U[id][1]  +  fields->U[id][2] * fields->U[id][2];
	c_scalar UdotC = info->lattice.c * ( fields->U[id][0] * info->lattice.vel[0][0]   +   fields->U[id][1] * info->lattice.vel[0][1]   +   fields->U[id][2] * info->lattice.vel[0][2] );
	c_scalar s_eq  = info->lattice.omega[0]  *  (  UdotC / info->lattice.cs2   +   UdotC * UdotC * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );	
	
	// Pressure at node
	fld[id] = ( info->lattice.cs2 / (1 - info->lattice.omega[0]) )  *  ( red   +  dot  * 0.5 * info->time.tstep   +   fields->rho[id] * s_eq );
	

	// Deallocate memory
	free(rhoGrad);
    }


    // Sync field
    syncScalarField( info, fld );    
    
}
