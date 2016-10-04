// Read field for c-written solvers

#include <readNeighbours.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


int** readNeighbours( const struct latticeInfo* lattice, const struct mpiInfo* parallel ) {

    int** field;
    
    // Open file
    std::ifstream inFile;
    std::ostringstream fileName;
    fileName << "processor" << parallel->pid << "/D" << lattice->d << "Q" << lattice->Q << "_lattice/neighbours" ;
    inFile.open( fileName.str().c_str() );
    if( !inFile.is_open() ) {
	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    uint np;
    inFile >> np;

    // Resize field
    field = (int**)malloc( np * sizeof(int*) );
    for(uint i = 0 ; i < np ; i++)
	field[i] = (int*)malloc( lattice->Q * sizeof(int) );
    
    // Read elements
    for(uint i = 0 ; i < np ; i++){
	for(uint j = 0 ; j < (uint)lattice->Q ; j++){
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
