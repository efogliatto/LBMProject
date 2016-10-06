#include <writePdfToVTK.h>
#include <writePdfField.h>
#include <stdio.h>
#include <stdlib.h>

void writePdfToVTK( char* fname, double** field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time ) {

    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", parallel->pid, time->current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\"  NumberOfComponents=\"%d\" format=\"ascii\">\n", fname, lattice->Q);

    // Print field
    unsigned int i,j;
    for( i = 0 ; i < lattice->nlocal + parallel->nghosts ; i++ ) {
	fprintf(outFile, "          ");
	for( j = 0 ; j < lattice->Q ; j++ ) {
	    fprintf(outFile, "%f ", field[i][j]);
	}
	fprintf(outFile, "\n");
    }

    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);



    // Write raw info
    writePdfField(fname, field, lattice, parallel, time);

}
