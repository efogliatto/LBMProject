#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

double** readVectorField(const char* fname, const struct Time t, const struct lattice lat) {

    unsigned int i,j;

    double** fld;    

    // Open file
    FILE* infile;
    char name[80];
    sprintf(name,"processor0/0/");
    strcat(name,fname);

    infile = fopen( name, "r" );
    if (!infile) { printf("Unable to open %s\n", name); }
    
    // Total number of points
    int np;
    fscanf(infile, "%d\n", &np);

    // Resize field
    fld = (double**)malloc( np * sizeof(double*) );
    for (i = 0 ; i < np ; i++) {
    	fld[i] = (double*)malloc(3 * sizeof(double));
    }
    
    // Read elements
    for(i = 0 ; i < np ; i++) {
	fscanf(infile, "%f", &fld[i][0]);
	fscanf(infile, "%f", &fld[i][1]);
	fscanf(infile, "%f", &fld[i][2]);
    }

    // Close file
    close(infile);
    
    return fld;

}
