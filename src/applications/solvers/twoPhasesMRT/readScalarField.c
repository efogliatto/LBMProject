#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

double* readScalarField(const char* fname, const struct Time t, const struct lattice lat) {

    unsigned int i,j;

    double* fld;    

    // Open file
    FILE* infile;
    char name[80];
    sprintf(name,"processor0/%d/",t.start);
    strcat(name,fname);

    infile = fopen( name, "r" );
    if (!infile) { printf("Unable to open %s\n", name); }
    
    // Total number of points
    int np;
    fscanf(infile, "%d\n", &np);

    // Resize field
    fld = (double*)malloc( np * sizeof(double) );
    
    // Read elements
    for(i = 0 ; i < np ; i++) {
	fscanf(infile, "%f", &fld[i]);
    }

    // Close file
    close(infile);
    
    return fld;

}
