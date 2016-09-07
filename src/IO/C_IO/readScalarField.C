// Read field for c-written solvers

#include <readScalarField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


c_scalar* readScalarField(const char* fname, const struct solverInfo* info) {

    // c_scalar* field;
    
    // // Open file
    // std::ifstream inFile;
    // std::ostringstream fileName;
    // fileName << "processor" << info->parallel.pid << "/" << info->time.start << "/" << fname << ".bin";
    // inFile.open( fileName.str().c_str(), std::ios::in | std::ios::binary );
    // if( !inFile.is_open() ) {
    // 	std::cout << "Unable to open file " << fileName << std::endl;
    // 	exit(1);
    // }    


    // // Resize field
    // unsigned int np = info->lattice.nlocal + info->parallel.nghosts;
    // field = (c_scalar*)malloc( np * sizeof(c_scalar) );

    // // Read elements
    // for(uint i = 0 ; i < np ; i++)
    // 	inFile.read( (char*)&field[i], sizeof(c_scalar) ); 
    
    // // Close file
    // inFile.close();


    // return field;
    




    // ASCII version
    
    c_scalar* field;
    
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
    field = (c_scalar*)malloc( np * sizeof(c_scalar) );
    
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
