#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

int** readNeighbours(const struct lattice lat) {

    unsigned int i,j;

    int** fld;    

    // Open file
    FILE* infile;
    char name[80];
    sprintf(name,"processor0/D%dQ%d_lattice/neighbours",lat.d,lat.Q);

    infile = fopen( name, "r" );
    if (!infile) { printf("Unable to open %s\n", name); }
    
    // Total number of points
    int np;
    fscanf(infile, "%d\n", &np);

    // Resize field
    fld = (int**)malloc( np * sizeof(int*) );
    for (i = 0 ; i < np ; i++) {
    	fld[i] = (int*)malloc(lat.Q * sizeof(int));
    }
    
    // Read elements
    for(i = 0 ; i < np ; i++) {
	for(j = 0 ; j < lat.Q ; j++) {
	    fscanf(infile, "%f", &fld[i][j]);
	}
    }

    // Close file
    close(infile);
    
    return fld;

}
