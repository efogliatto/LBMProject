// Read field for c-written solvers

#include <readScalarField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


double* readScalarField(const char* fname, const struct solverInfo* info) {

    double* field;
    
    // Open file
    std::ifstream inFile;
    std::ostringstream fileName;
    fileName << "processor" << info->parallel.pid << "/" << info->time.start << "/" << fname;
    inFile.open( fileName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    uint np;
    inFile >> np;

    // Resize field
    field = (double*)malloc( np * sizeof(double) );
    
    // Read elements
    for(uint i = 0 ; i < np ; i++)
    	inFile >> field[i];
    
    // Close file
    inFile.close();


    return field;
    
}


#ifdef __cplusplus
}
#endif
