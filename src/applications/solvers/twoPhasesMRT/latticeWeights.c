#include <stdio.h>
#include "data.h"
#include <stdlib.h>

double* latticeWeights(const struct lattice lat) {

    double* omega;

    if(  (lat.d == 2) && (lat.Q == 9)  )  {

	unsigned int i;
	omega = (double*)malloc( lat.Q * sizeof(double) );

	omega[0] = 4.0 / 9.0;
	omega[1] = 1.0 / 9.0;
	omega[2] = 1.0 / 9.0;
	omega[3] = 1.0 / 9.0;
	omega[4] = 1.0 / 9.0;
	omega[5] = 1.0 / 36.0;
	omega[6] = 1.0 / 36.0;
	omega[7] = 1.0 / 36.0;
	omega[8] = 1.0 / 36.0;
	omega[9] = 1.0 / 36.0;
	
    }
    
    return omega;
    
}
