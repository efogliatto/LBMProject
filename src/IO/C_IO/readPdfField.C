// Read field for c-written solvers

#include <readPdfField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


double** readPdfField(const char* fname, const struct solverInfo* info) {

    double** field;
    
    // Open file
    std::ifstream inFile;
    std::ostringstream fileName;
    fileName << "processor0/" << info->time.start << "/" << fname;
    inFile.open( fileName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    uint np;
    inFile >> np;

    // Resize field
    field = (double**)malloc( np * sizeof(double*) );
    for(uint i = 0 ; i < np ; i++)
	field[i] = (double*)malloc( info->lattice.Q * sizeof(double) );
    
    // Read elements
    for(uint i = 0 ; i < np ; i++){
	for(uint j = 0 ; j < (uint)info->lattice.Q ; j++){
	    inFile >> field[i][j];
	}
    }
    
    // Close file
    inFile.close();


    return field;
    
}


#ifdef __cplusplus
}
#endif
