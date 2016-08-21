// Matrix for h field

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

double** lbModelM(const struct lattice lat);
double** lbModelInvM(const struct lattice lat);

double** sourceMatrix(const struct lattice lat, const struct fields fld) {

    double** sm;

    unsigned int i,j,k;
    sm = (double**)malloc( lat.Q * sizeof(double*) );
    for (i = 0 ; i < lat.Q ; i++) {
	sm[i] = (double*)malloc(lat.Q * sizeof(double));
    }

    for (i = 0 ; i < lat.Q ; i++) {
	sm[i][i] = 1.0 - (0.5 * fld.Sh[i]);
    }



    double** res;
    res = (double**)malloc( lat.Q * sizeof(double*) );
    double** res2;
    res2 = (double**)malloc( lat.Q * sizeof(double*) );    
    for (i = 0 ; i < lat.Q ; i++) {
	res[i] = (double*)malloc(lat.Q * sizeof(double));
	res2[i] = (double*)malloc(lat.Q * sizeof(double));
    }

    for (i = 0 ; i < lat.Q ; i++) {
	for (j = 0 ; j < lat.Q ; j++) {
	    res[i][j] = 0;
	    res2[i][j] = 0;
	}
    }


    double** M;
    double** invM;

    M = lbModelM(lat);
    invM = lbModelInvM(lat);
    
    // Matrix mutiplication
    for (i = 0 ; i < lat.Q ; i++) {
	for (j = 0 ; j < lat.Q ; j++) {
	    for (k = 0 ; k < lat.Q ; k++) {
		res[i][j] += sm[i][k] * M[k][j];
	    }
	}
    }

    for (i = 0 ; i < lat.Q ; i++) {
	for (j = 0 ; j < lat.Q ; j++) {
	    for (k = 0 ; k < lat.Q ; k++) {
		res2[i][j] += res[i][k] * invM[k][j];
	    }
	}
    }    
    

    return res2;
    
}
