#include <pseudoPotCollision.h>
#include <liEquilibrium.h>
#include <stdlib.h>
#include <matVecMult.h>
#include <liMRTForce.h>
#include <totalForce.h>
#include <potential.h>
#include <syncPdfField.h>

void pseudoPotCollision( struct liModelInfo* info, double* T, double* rho, double** v, int** nb, double** f ) {

    // Indices
    unsigned int id, k;

    
    // Partial distributions
    double* alpha = (double*)malloc( info->lattice.Q * sizeof(double) );   // f - f_eq
    double* beta  = (double*)malloc( info->lattice.Q * sizeof(double) );   // Lambda * (f - f_eq)
    double* gamma = (double*)malloc( info->lattice.Q * sizeof(double) );   // Delta * S
    double* Sbar  = (double*)malloc( info->lattice.Q * sizeof(double) );   // MRT force
    double* S     = (double*)malloc( info->lattice.Q * sizeof(double) );   // MRT force

    
    // Interaction force
    double Fm[3];

    // Total force
    double F[3];

    
    // Move over points
    for( id = 0 ; id < info->lattice.nlocal ; id++ ) {

	// Compute equilibrium
	liEquilibrium(info, rho[id], v[id], alpha);

	// Update alpha. alpha = f - f_eq
	for( k = 0 ; k < info->lattice.Q ; k++ ) {
	    alpha[k] = f[id][k] - alpha[k];
	}

	// Update Beta. beta = Lambda * (f - f_eq)
	matVecMult(info->fields.Lambda, alpha, beta, info->lattice.Q);

	// Interaction force
	interactionForce( info, Fm, rho, nb, T[id], id);

	// Total force
	totalForce( info, F, rho, nb, T[id], id);	

	// MRT force
	double psi = potential(info, rho[id], T[id]);
	liMRTForce(info, v[id], F, Fm, psi, Sbar);
	
	// Force in velocity space. S = inv(M) * S_bar
	matVecMult(info->fields.invM, Sbar, S, info->lattice.Q);

	// Update gamma. gamma = LambdaBar * S
	matVecMult(info->fields.Lambda, S, gamma, info->lattice.Q);
	
	// Collide f
	for( k = 0 ; k < info->lattice.Q ; k++ ) {

	    f[id][k] = f[id][k] - beta[k] + info->time.tstep * (S[k] - 0.5 * gamma[k]);

	}


    }


    // Deallocate memory
    free(alpha);
    free(beta);
    free(gamma);
    free(Sbar);
    free(S);


    // Synchronize field
    syncPdfField( &info->parallel, f, info->lattice.Q );

}
