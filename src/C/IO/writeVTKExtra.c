#include <writeVTKExtra.h>
#include <stdio.h>
#include <stdlib.h>

void writeVTKExtra( struct vtkInfo* vtk, struct mpiInfo* parallel, struct timeInfo* time ) {


    FILE *outFile;

    char fileName[100];

    // Create folder
    sprintf(fileName, "mkdir -p processor%d/%d", parallel->pid, time->current);
    system(fileName);


    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", parallel->pid, time->current);

    outFile = fopen(fileName, "a");

    fprintf(outFile, "      </PointData>\n");
    fprintf(outFile, "    </Piece>\n");
    fprintf(outFile, "  </UnstructuredGrid>\n");
    fprintf(outFile, "</VTKFile>\n");

    fclose(outFile);


}
