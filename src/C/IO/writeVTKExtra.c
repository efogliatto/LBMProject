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



    // Write case.pvd

    if(parallel->pid == 0) {
    
	// Remove last two lines
	char cmd[100];
	sprintf(cmd, "head -n -2 < case.pvd > case2.pvd");
	system(cmd);

	sprintf(cmd, "mv case2.pvd case.pvd");
	system(cmd);


	// Open file
	sprintf(fileName, "case.pvd");
	outFile = fopen(fileName, "a");
	
	// Add line
	fprintf(outFile, "    <DataSet part=\"0\"  timestep=\"%d\" file=\"%d/fields.pvtu\" />\n", time->current, time->current );
	fprintf(outFile, "  </Collection>\n");
	fprintf(outFile, "</VTKFile>\n");


	fclose(outFile);
	
    }


}
