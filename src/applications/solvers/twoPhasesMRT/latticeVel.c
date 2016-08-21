#include <stdio.h>
#include "data.h"
#include <stdlib.h>

int** latticeVel(const struct lattice lat) {

    int** vel;

    if(  (lat.d == 2) && (lat.Q == 9)  )  {

	unsigned int i;
	vel = (int**)malloc( lat.Q * sizeof(int*) );
	for (i = 0 ; i < lat.Q ; i++) {
	    vel[i] = (int*)malloc(3 * sizeof(int));
	}
	
	// Model velocity
	vel[0][0] = 0;
	vel[0][1] = 0;
	vel[0][0] = 0;
    
	vel[1][0] = -1;
	vel[1][1] = 0;
	vel[1][0] = 0;

	vel[2][0] = 0;
	vel[2][1] = -1;
	vel[2][0] = 0;

	vel[3][0] = 1;
	vel[3][1] = 0;
	vel[3][0] = 0;

	vel[4][0] = 0;
	vel[4][1] = 1;
	vel[4][0] = 0;

	vel[5][0] = -1;
	vel[5][1] = -1;
	vel[5][0] = 0;

	vel[6][0] = 1;
	vel[6][1] = -1;
	vel[6][0] = 0;

	vel[7][0] = 1;
	vel[7][1] = 1;
	vel[7][0] = 0;

	vel[8][0] = -1;
	vel[8][1] = 1;
	vel[8][0] = 0;

    }
    
    return vel;
    
}
