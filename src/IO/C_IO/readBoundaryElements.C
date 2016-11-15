// Read information for c-written solvers

#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <readBoundaryElements.h>


#ifdef __cplusplus
extern "C" {
#endif


    struct bdInfo readBoundaryElements( int pid, int d, int Q ) {

    struct bdInfo info;


    // Open file
    std::ifstream inFile;
    std::ostringstream fileName;
    fileName << "processor" << pid << "/D" << d << "Q" << Q << "_lattice/boundary" ;
    inFile.open( fileName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    



    // Total number boundaries
    inFile >> info._nb;

    // Allocate memory
    info._nbel = (uint*)malloc( info._nb * sizeof(uint) );
    info._bdNames = (char**)malloc( info._nb * sizeof(char*) );
    

    // Read each boundary
    for( uint i = 0 ; i < info._nb ; i++ ) {

	// // Boundary name
	// std::string bdn;
	// inFile >> bdn;

	// info._bdNames[i] = new char[bdn.length() + 1];
	// std::strcpy(info._bdNames[i], bdn.c_str());

    }



    
    return info;
    
}


#ifdef __cplusplus
}
#endif
