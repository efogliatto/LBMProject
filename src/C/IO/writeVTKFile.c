#include <writeVTKFile.h>
#include <stdio.h>
#include <stdlib.h>

void writeVTKFile( struct vtkInfo* vtk, struct mpiInfo* parallel, struct latticeInfo* lattice, struct timeInfo* time ) {

    FILE *outFile;

    char fileName[100];

    // Create folder
    sprintf(fileName, "mkdir -p processor%d/%d", parallel->pid, time->current);
    system(fileName);


    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", parallel->pid, time->current);

    outFile = fopen(fileName, "w");



    // Print header
    fprintf(outFile, "<?xml version=\"1.0\"?>\n");
    fprintf(outFile, "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\" compressor=\"vtkZLibDataCompressor\">\n");
    fprintf(outFile, "  <UnstructuredGrid>\n");
    fprintf(outFile, "    <Piece NumberOfPoints=\"%d\" NumberOfCells=\"%d\">\n", vtk->np, vtk->ncells);
    fprintf(outFile, "      <Points>\n");
    fprintf(outFile, "        <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n");

    
    // Write points
    unsigned int i;
    for( i = 0 ; i < vtk->np ; i++ ) {
    	fprintf(outFile, "          %f %f %f\n", vtk->points[i][0], vtk->points[i][1], vtk->points[i][2]);
    }
    

    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "      </Points>\n");
    fprintf(outFile, "      <Cells>\n");
    fprintf(outFile, "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n");

    // Write cells
    unsigned int j;
    for( i = 0 ; i < vtk->ncells ; i++ ) {
	fprintf(outFile, "          ");
    	for( j = 0 ; j < vtk->cells[i][0] ; j++ ) {
    	    fprintf(outFile, "%d ", vtk->cells[i][j+1]);
    	}
    	fprintf(outFile, "\n");
    }


    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n");


    // Write offsets
    unsigned int acum = 0;
    for( i = 0 ; i < vtk->ncells ; i++ ) {
    	acum += vtk->cells[i][0];
    	fprintf(outFile, "          %d\n", acum);
    }


    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n");


    // Write cell type
    for( i = 0 ; i < vtk->ncells ; i++ ) {
    	fprintf(outFile, "          8\n");
    }


    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "      </Cells>\n");

    // Write field names
    fprintf(outFile, "      <PointData Scalars=\"");
    for( i = 0 ; i < vtk->nscalar ; i++ ) {
	if(i == (vtk->nscalar - 1)) {
	    fprintf(outFile, "%s", vtk->scalarFields[i]);
	}
	else {	    
	    fprintf(outFile, "%s ", vtk->scalarFields[i]);
	}
    }

    fprintf(outFile, "\" Vectors=\"");
    for( i = 0 ; i < vtk->nvector ; i++ ) {
    	fprintf(outFile, "%s ", vtk->vectorFields[i]);
    }
    for( i = 0 ; i < vtk->npdf ; i++ ) {
	if(i == (vtk->npdf - 1)) {
	    fprintf(outFile, "%s", vtk->pdfFields[i]);
	}
	else {
	    fprintf(outFile, "%s ", vtk->pdfFields[i]);
	}
    }

    
    fprintf(outFile, "\">\n");
    
    fclose(outFile);





    // Write in time folder
    if( parallel->pid == 0 ) {

	// Create folder
	sprintf(fileName, "mkdir -p %d", time->current);
	system(fileName);


	// Open file
	sprintf(fileName, "%d/fields.pvtu", time->current);
	outFile = fopen(fileName, "w");


	// Write header
	fprintf(outFile, "<?xml version=\"1.0\"?>\n");
	fprintf(outFile, "<VTKFile type=\"PUnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
	fprintf(outFile, "  <PUnstructuredGrid GhostLevel=\"0\">\n");


	// Write fields info
	fprintf(outFile, "    <PPointData Scalars=\"");
	for( i = 0 ; i < vtk->nscalar ; i++ ) {
	    if(i == (vtk->nscalar - 1)) {
		fprintf(outFile, "%s", vtk->scalarFields[i]);
	    }
	    else {	    
		fprintf(outFile, "%s ", vtk->scalarFields[i]);
	    }
	}

	fprintf(outFile, "\" Vectors=\"");
	for( i = 0 ; i < vtk->nvector ; i++ ) {
	    fprintf(outFile, "%s ", vtk->vectorFields[i]);
	}
	for( i = 0 ; i < vtk->npdf ; i++ ) {
	    if(i == (vtk->npdf - 1)) {
		fprintf(outFile, "%s", vtk->pdfFields[i]);
	    }
	    else {
		fprintf(outFile, "%s ", vtk->pdfFields[i]);
	    }
	}

	fprintf(outFile, "\">\n");

	

	// Write scalar fields info
	for (i = 0 ; i < vtk->nscalar ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\"/>\n", vtk->scalarFields[i]);
	}

	// Write vector fields info
	for (i = 0 ; i < vtk->nvector ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\" NumberOfComponents=\"3\"/>\n", vtk->vectorFields[i]);
	}

	// Write pdf fields info
	for (i = 0 ; i < vtk->npdf ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\" NumberOfComponents=\"%d\"/>\n", vtk->pdfFields[i], lattice->Q);
	}		



	fprintf(outFile, "    </PPointData>\n");
	fprintf(outFile, "    <PPoints>\n");
	fprintf(outFile, "      <PDataArray type=\"Float32\" NumberOfComponents=\"3\"/>\n");
	fprintf(outFile, "    </PPoints>\n");
	for (i = 0 ; i < vtk->npdf ; i++) {
	    fprintf(outFile, "    <Piece Source=\"../processor0/%d/fields.vtu\"/>\n", time->current);
	}
	fprintf(outFile, "  </PUnstructuredGrid>\n");
	fprintf(outFile, "</VTKFile>\n");


	
	fclose(outFile);

    }

    

}
