#include <writeScalarToVTK.h>
#include <writeScalarField.h>
#include <stdio.h>
#include <stdlib.h>

void writeScalarToVTK( char* fname, double* field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time ) {

    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", parallel->pid, time->current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\" format=\"ascii\">\n", fname);

    // Print field
    unsigned int i;
    for( i = 0 ; i < lattice->nlocal + parallel->nghosts ; i++ ) {
	fprintf(outFile, "          %f\n", field[i]);
    }

    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);



    // Write raw info
    writeScalarField(fname, field, lattice, parallel, time);

}
