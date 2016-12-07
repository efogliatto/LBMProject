#include <liMRTCollision.h>
#include <stdlib.h>
#include <matVecMult.h>
#include <liMRTForce.h>
#include <totalForce.h>
#include <potential.h>
#include <syncPdfField.h>


void liMRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    unsigned int id, k;

    
    /* // Partial distributions */
    double* m     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // m:  momentum space
    double* m_eq  = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // meq: equilibrium in momentum space
    double* S     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // MRT force

    
    // Move over points
    for( id = 0 ; id < mesh->lattice.nlocal ; id++ ) {
	
	double umag = mfields->U[id][0] * mfields->U[id][0]  +  mfields->U[id][1] * mfields->U[id][1];
	
	// Compute equilibrium in momentum space
	m_eq[0] = mfields->rho[id];
	m_eq[1] = mfields->rho[id] * (-2 + 3*umag);
	m_eq[2] = mfields->rho[id] * (1 - 3*umag);
	m_eq[3] = mfields->rho[id] * mfields->U[id][0];
	m_eq[4] = mfields->rho[id] * (-mfields->U[id][0]);
	m_eq[5] = mfields->rho[id] * mfields->U[id][1];
	m_eq[6] = mfields->rho[id] * (-mfields->U[id][1]);
	m_eq[7] = mfields->rho[id] * (mfields->U[id][0]*mfields->U[id][0] - mfields->U[id][1]*mfields->U[id][1]);
	m_eq[8] = mfields->rho[id] * mfields->U[id][0] * mfields->U[id][1];

	
	// Distribution in momentum space
	matVecMult(mesh->lattice.M, field->value[id], m, mesh->lattice.Q);

	// Total Force
	liMRTForce( mesh, mfields, field, S, id);

	
	// Collision in momentum space
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    m[k] = m[k]  -  field->Lambda[k]*( m[k] - m_eq[k] )  + mesh->time.tstep * ( 1 - 0.5*field->Lambda[k] ) * S[k];
	    
	}

	
	// Back to phase space
	matVecMult(mesh->lattice.invM, m, field->value[id], mesh->lattice.Q);
	
    }


    // Deallocate memory
    free(m);
    free(m_eq);
    free(S);


    // Synchronize field
    syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q );


    
}







    /* // Indices */
    /* unsigned int id, k; */

    
    /* // Partial distributions */
    /* double* alpha = (double*)malloc( info->lattice.Q * sizeof(double) );   // f - f_eq */
    /* double* beta  = (double*)malloc( info->lattice.Q * sizeof(double) );   // Lambda * (f - f_eq) */
    /* double* gamma = (double*)malloc( info->lattice.Q * sizeof(double) );   // Delta * S */
    /* double* Sbar  = (double*)malloc( info->lattice.Q * sizeof(double) );   // MRT force */
    /* double* S     = (double*)malloc( info->lattice.Q * sizeof(double) );   // MRT force */

    
    /* // Interaction force */
    /* double Fm[3]; */

    /* // Total force */
    /* double F[3]; */

    
    /* // Move over points */
    /* for( id = 0 ; id < info->lattice.nlocal ; id++ ) { */

    /* 	// Compute equilibrium */
    /* 	liEquilibrium(info, rho[id], v[id], alpha); */

    /* 	// Update alpha. alpha = f - f_eq */
    /* 	for( k = 0 ; k < info->lattice.Q ; k++ ) { */
    /* 	    alpha[k] = f[id][k] - alpha[k]; */
    /* 	} */

    /* 	// Update Beta. beta = Lambda * (f - f_eq) */
    /* 	matVecMult(info->fields.Lambda, alpha, beta, info->lattice.Q); */

    /* 	// Interaction force */
    /* 	interactionForce( info, Fm, rho, nb, T, id); */

    /* 	// Total force */
    /* 	totalForce( info, F, rho, nb, T, id);	 */

    /* 	// MRT force */
    /* 	double psi = potential(info, rho[id], T[id]); */
    /* 	liMRTForce(info, v[id], F, Fm, psi, Sbar); */
	
    /* 	// Force in velocity space. S = inv(M) * S_bar */
    /* 	matVecMult(info->fields.invM, Sbar, S, info->lattice.Q); */

    /* 	// Update gamma. gamma = LambdaBar * S */
    /* 	matVecMult(info->fields.Lambda, S, gamma, info->lattice.Q); */
	
    /* 	// Collide f */
    /* 	for( k = 0 ; k < info->lattice.Q ; k++ ) { */

    /* 	    f[id][k] = f[id][k] - beta[k] + info->time.tstep * (S[k] - 0.5 * gamma[k]); */

    /* 	} */


    /* } */


    /* // Deallocate memory */
    /* free(alpha); */
    /* free(beta); */
    /* free(gamma); */
    /* free(Sbar); */
    /* free(S); */


    /* // Synchronize field */
    /* syncPdfField( &info->parallel, f, info->lattice.Q ); */
