// Write field for c-written solvers

#include <writePdfField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


void writePdfField( char* fname, c_scalar** field, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time ) {

    // Create folder if it does not exist
    std::ostringstream fileName;
    fileName << "processor" << parallel->pid << "/" << time->current << "/";
    system( ("mkdir -p " + fileName.str()).c_str() );
    
    
    // Open file
    std::ofstream outFile;
    fileName << fname;
    outFile.open( fileName.str().c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    outFile << lattice->nlocal + parallel->nghosts << std::endl;
    
    // Write elements
    for(uint i = 0 ; i < lattice->nlocal + parallel->nghosts; i++) {
	for(uint j = 0 ; j < (uint)lattice->Q ; j++) {
	    outFile << field[i][j] << " ";
	}
	outFile << std::endl;
    }
    
    // Close file
    outFile.close();

}


#ifdef __cplusplus
}
#endif
