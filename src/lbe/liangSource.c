#include <liangSource.h>
#include <matVecMult.h>
#include <stdlib.h>
#include <stdio.h>
#include <scalarFieldGradient.h>
#include <scalarFieldLaplacian.h>
#include <biasedGradient.h>
#include <stringHash.h>
#include <string.h>


void liangSource(struct twoPhasesFields* fields, struct solverInfo* info, c_scalar* sourceTerm, unsigned int id) {

    unsigned int j, k;

    int scheme = -1;

    // Schemes
    char* dd[] = {"central", "biased"};
    for( k = 0 ; k < 2 ; k++ ) {
	if( strcmp(dd[k], info->lattice.dd) == 0 ) {
	    scheme = k;
	}
    }

    
    // Surface tension force
    c_scalar* Fs = scalarFieldGradient( fields, info, fields->phi, id );
    for( k = 0 ; k < 3 ; k++) {
	Fs[k] = Fs[k] * fields->muPhi[id];
    }

    
    // Interfacial force
    c_scalar lap = scalarFieldLaplacian( fields, info, fields->muPhi, id );    
    c_scalar* Fa = (c_scalar*)malloc( 3 * sizeof(c_scalar) );
    for( k = 0 ; k < 3 ; k++) {
	Fa[k] = fields->U[id][k]* info->fields.M_phi * lap * (info->fields.rho_A - info->fields.rho_B) / (info->fields.phi_A - info->fields.phi_B);
    }
    

    // Body force
    c_scalar* Fb = (c_scalar*)malloc( 3 * sizeof(c_scalar) );
    Fb[0] = info->fields.gx * fields->rho[id];
    Fb[1] = info->fields.gy * fields->rho[id];
    Fb[2] = info->fields.gz * fields->rho[id];


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
    
   

    for( k = 0 ; k < 3 ; k++) {
    	rhoGrad[k] = rhoGrad[k] * info->lattice.cs2;
    }    
    


    // Source term
    c_scalar* st = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );

    for( k = 0 ; k < info->lattice.Q ; k++) {

	// Dot product
	c_scalar dot = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    dot += info->lattice.c * info->lattice.vel[k][j] * fields->U[id][j];
	}


	// Velocity magnitude
	c_scalar Umag = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    Umag += fields->U[id][j] * fields->U[id][j];
	}
	
	st[k] = info->lattice.omega[k]  *  (  dot / info->lattice.cs2   +   dot * dot * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );

    }

    
    // Gamma function
    c_scalar* Gamma = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );
    for( k = 0 ; k < info->lattice.Q ; k++) {
	Gamma[k] = info->lattice.omega[k] + st[k];
    }
    
    c_scalar* Gamma0 = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );
    for( k = 0 ; k < info->lattice.Q ; k++) {
	Gamma0[k] = info->lattice.omega[k];
    }    


    // Total force
    c_scalar* Force = (c_scalar*)malloc( info->lattice.Q * sizeof(c_scalar) );
    for( k = 0 ; k < info->lattice.Q ; k++) {

	// Auxiliar components
	c_scalar aux[3];

	for( j = 0 ; j < 3 ; j++) {
	    aux[j] = rhoGrad[j] * (Gamma[k] - Gamma0[k])  +  (Fs[j] + Fa[j] + Fb[j]) * Gamma[k];
	}


	// Dot product
	Force[k] = 0;
	for( j = 0 ; j < 3 ; j++) {
	    Force[k] += info->time.tstep * (info->lattice.vel[k][j] * info->lattice.c - fields->U[id][j]) * aux[j] / info->lattice.cs2;
	}
	
    }

    
    // Multiplication with source matrix
    if(fields->phi[id] < 0) {
	
	matVecMult(info->fields.srcMatA, Force, sourceTerm, info->lattice.Q);
	
    }
    
    else {
	
    	matVecMult(info->fields.srcMatB, Force, sourceTerm, info->lattice.Q);

    }

    
    // Memory deallocation
    free(Fa);
    free(Fb);
    free(Fs);
    free(st);
    free(Gamma);
    free(Gamma0);
    free(Force);
    free(rhoGrad);
    
}
