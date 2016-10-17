#include <writeVectorToVTK.h>
#include <writeVectorField.h>
#include <stdio.h>
#include <stdlib.h>

void writeVectorToVTK( char* fname, double** field, struct latticeInfo* lattice, struct mpiInfo* parallel, struct timeInfo* time ) {

    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", parallel->pid, time->current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\"  NumberOfComponents=\"3\" format=\"ascii\">\n", fname);

    // Print field
    unsigned int i;
    for( i = 0 ; i < lattice->nlocal + parallel->nghosts ; i++ ) {
	fprintf(outFile, "          %f %f %f\n", field[i][0], field[i][1], field[i][2]);
    }

    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);



    // Write raw info
    writeVectorField(fname, field, lattice, parallel, time);

}
