// Read field for c-written solvers

#include <readVTKInfo.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <Vector3.h>
#include <dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif


struct vtkInfo readVTKInfo( const struct latticeInfo* lattice, const struct mpiInfo* parallel ) {

    struct vtkInfo info;

    /* ------------------------------------------------ */
    /*                     Points                       */
    /* ------------------------------------------------ */
    
    std::ifstream inFile;
    std::ostringstream fileName;
    fileName << "processor" << parallel->pid << "/D" << lattice->d << "Q" << lattice->Q << "_lattice/points" ;
    inFile.open( fileName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    inFile >> info.np;

    // Resize field
    info.points = (double**)malloc( info.np * sizeof(double*) );
    for(uint i = 0 ; i < info.np ; i++)
	info.points[i] = (double*)malloc( 3 * sizeof(double) );
    
    // Read elements
    Vector3 pt;
    for(uint i = 0 ; i < info.np ; i++){

	inFile >> pt;

	info.points[i][0] = pt.x();
	info.points[i][1] = pt.y();
	info.points[i][2] = pt.z();
	
    }
    
    // Close file
    inFile.close();




    /* ------------------------------------------------ */
    /*                     Cells                        */
    /* ------------------------------------------------ */
    
    std::ostringstream cellName;
    cellName << "processor" << parallel->pid << "/D" << lattice->d << "Q" << lattice->Q << "_lattice/vtkCells" ;
    inFile.open( cellName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << cellName.str() << std::endl;
    	exit(1);
    }    

    
    // Total number of cells
    inFile >> info.ncells;

    // Resize field
    info.cells = (uint**)malloc( info.ncells * sizeof(uint*) );
    for(uint i = 0 ; i < info.ncells ; i++)
	info.cells[i] = (uint*)malloc( 9 * sizeof(uint) );
    
    // Read elements
    for(uint i = 0 ; i < info.ncells ; i++){

	inFile >> info.cells[i][0];

	for( uint j = 0 ; j < info.cells[i][0] ; j++ ) {

	    inFile >> info.cells[i][j+1];
	    
	}
	
    }
    
    // Close file
    inFile.close();
    





    
    /* ------------------------------------------------ */
    /*                     Fields                       */
    /* ------------------------------------------------ */

    
    dictionary dict("properties/startFields");

    
    // Fields list
    std::vector<std::string> fields = dict.lookUpEntryList<string>("fields/valuesList");

    
    // Check type and add to list
    info.nscalar = 0;
    info.nvector = 0;
    info.npdf = 0;

    for(auto fld : fields) {

	std::string ftype = dict.lookUpEntry<string>(fld + "/type");

	if( ftype.compare("latticeScalarField") == 0 ) {   info.nscalar++;  }
	if( ftype.compare("latticeVectorField") == 0 ) {   info.nvector++;  }
	if( ftype.compare("latticePdfField")    == 0 ) {   info.npdf++;  }

    }


    // Resize lists
    info.scalarFields = (char**)malloc( info.nscalar * sizeof(char*) );
    info.vectorFields = (char**)malloc( info.nvector * sizeof(char*) );
    info.pdfFields    = (char**)malloc( info.npdf * sizeof(char*) );


    uint sid(0), vid(0), pid(0);
    for(auto fld : fields) {

	std::string ftype = dict.lookUpEntry<string>(fld + "/type");

	if( ftype.compare("latticeScalarField") == 0 ) {

	    info.scalarFields[sid] = new char[fld.length() + 1];

	    std::strcpy( info.scalarFields[sid], fld.c_str() );
	    
	    sid++;

	}

	
	if( ftype.compare("latticeVectorField") == 0 ) {

	    info.vectorFields[vid] = new char[fld.length() + 1];

	    std::strcpy( info.vectorFields[vid], fld.c_str() );
	    
	    vid++;

	}

	
	if( ftype.compare("latticePdfField")    == 0 ) {

	    info.pdfFields[pid] = new char[fld.length() + 1];

	    std::strcpy( info.pdfFields[pid], fld.c_str() );
	    
	    pid++;

	}

    }




    
    
    return info;
    
}


#ifdef __cplusplus
}
#endif
