#include <liMRTForce.h>
#include <stdio.h>
#include <totalForce.h>
#include <interactionForce.h>
#include <potential.h>


void liMRTForce( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, double* S, unsigned int id ) {

    if( mesh->lattice.Q == 9 ) {

	double F[3];
	double Fm[3];
	
	// Total force
	totalForce( mesh, F, mfields->rho, mfields->T, id);

	// Interaction force
	interactionForce( mesh, Fm, mfields->rho, mfields->T, id);

	// Potential
	double psi = potential( mesh, mfields->rho[id], mfields->T[id]);
	
	S[0] = 0;
	S[1] =  6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) + 12 * field->sigma * (Fm[0]*Fm[0] + Fm[1]*Fm[1]) / (psi * psi * mesh->time.tstep*((1/field->Lambda[1])-0.5));
	S[2] = -6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) - 12 * field->sigma * (Fm[0]*Fm[0] + Fm[1]*Fm[1]) / (psi * psi * mesh->time.tstep*((1/field->Lambda[2])-0.5));
	S[3] = F[0];
	S[4] = -F[0];
	S[5] = F[1];
	S[6] = -F[1];
	S[7] = 2 * (mfields->U[id][0]*F[0] - mfields->U[id][1]*F[1]);
	S[8] = mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1];
	
    }

    else {

    	if( mesh->parallel.pid == 0 ) {

    	    printf("\n [ERROR] MRT force squeme not implemented for D%dQ%d \n\n", mesh->lattice.d, mesh->lattice.Q);
	    
    	}

    }

}
