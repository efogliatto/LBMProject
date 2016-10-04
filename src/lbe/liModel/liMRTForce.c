#include <liMRTForce.h>
#include <stdio.h>

void liMRTForce( struct liModelInfo* info, double v[3], double F[3], double* S ) {

    if( info->lattice.Q == 9 ) {

	S[0] = 0;
	S[1] = 6 * (v[0]*F[0] + v[1]*F[1]);
	S[2] = -6 * (v[0]*F[0] + v[1]*F[1]);
	S[3] = F[0];
	S[4] = -F[0];
	S[5] = F[1];
	S[6] = -F[1];
	S[7] = 2 * (v[0]*F[0] - v[1]*F[1]);
	S[8] = v[0]*F[0] + v[1]*F[1];
	
    }

    else {

	if( info->parallel.pid == 0 ) {

	    printf("\n [ERROR] MRT force squeme not implemented for D%dQ%d \n\n", info->lattice.d, info->lattice.Q);
	    
	}

    }

}
