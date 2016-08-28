#include <liangSource.h>
#include <matVecMult.h>
#include <stdlib.h>
#include <stdio.h>
#include <scalarFieldGradient.h>
#include <scalarFieldLaplacian.h>

void liangSource(struct twoPhasesFields* fields, const struct solverInfo* info, double* sourceTerm, const unsigned int id) {

    unsigned int i, j, k;

/* 	vector<Vector3> lvel = _p->_lat.lbmodel()->latticeVel(); */
/* 	for(uint i = 0 ; i < lvel.size() ; i++) */
/* 	    lvel[i] = (lvel[i] * _p->_lat.lbmodel()->c()   -   u->value() )  /  cs2 ; */


    // Surface tension force
    double* Fs = scalarFieldGradient( fields, info, fields->phi, id );
    for( k = 0 ; k < 3 ; k++) {
	Fs[k] = Fs[k] * fields->muPhi[id];
    }

    
    // Interfacial force
    double lap = scalarFieldLaplacian( fields, info, fields->muPhi, id );    
    double* Fa = (double*)malloc( 3 * sizeof(double) );
    for( k = 0 ; k < 3 ; k++) {
	Fa[k] = fields->U[id][k]* info->fields.M_phi * lap * (info->fields.rho_A - info->fields.rho_B) / (info->fields.phi_A - info->fields.phi_B);
    }
    

    // Body force
    double* Fb = (double*)malloc( 3 * sizeof(double) );
    Fb[0] = info->fields.gx * fields->rho[id];
    Fb[1] = info->fields.gy * fields->rho[id];
    Fb[2] = info->fields.gz * fields->rho[id];


    // Density gradient
    double* rhoGrad = scalarFieldGradient( fields, info, fields->rho, id );
    for( k = 0 ; k < 3 ; k++) {
	rhoGrad[k] = rhoGrad[k] * info->lattice.cs2;
    }


    // Source term
    double* st = (double*)malloc( info->lattice.Q * sizeof(double) );

    for( k = 0 ; k < info->lattice.Q ; k++) {

	// Dot product
	double dot = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    dot += info->lattice.c * info->lattice.vel[k][j] * fields->U[id][j];
	}


	// Velocity magnitude
	double Umag = 0;
	for( j = 0 ; j < 3 ; j++ ) {
	    Umag += fields->U[id][j] * fields->U[id][j];
	}
	
	st[k] = info->lattice.omega[k]  *  (  dot / info->lattice.cs2   +   dot * dot * 0.5 / (info->lattice.cs2 * info->lattice.cs2)   -  Umag * 0.5 / info->lattice.cs2 );

    }

    
    // Gamma function
    double* Gamma = (double*)malloc( info->lattice.Q * sizeof(double) );
    for( k = 0 ; k < info->lattice.Q ; k++) {
	Gamma[k] = info->lattice.omega[k] + st[k];
    }
    
    double* Gamma0 = (double*)malloc( info->lattice.Q * sizeof(double) );
    for( k = 0 ; k < info->lattice.Q ; k++) {
	Gamma0[k] = info->lattice.omega[k];
    }    


    // Total force
    double* Force = (double*)malloc( info->lattice.Q * sizeof(double) );
    for( k = 0 ; k < info->lattice.Q ; k++) {

	// Auxiliar components
	double aux[3];

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
