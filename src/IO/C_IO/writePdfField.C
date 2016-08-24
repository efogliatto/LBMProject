// Write field for c-written solvers

#include <writePdfField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


void writePdfField(const char* fname, const double** field, const struct solverInfo* info) {

    // Open file
    std::ofstream outFile;
    std::ostringstream fileName;
    fileName << "processor0/" << info->time.current << "/" << fname;
    outFile.open( fileName.str().c_str() );
    if( !outFile.is_open() ) {
    	std::cout << "Unable to open file " << fileName << std::endl;
    	exit(1);
    }    

    
    // Total number of points
    outFile << info->lattice.nlocal << std::endl;
    
    // Write elements
    for(uint i = 0 ; i < info->lattice.nlocal ; i++) {
	for(uint j = 0 ; j < (uint)info->lattice.Q ; j++) {
	    outFile << field[i][j] << "  ";
	}
	outFile << std::endl;
    }
    
    // Close file
    outFile.close();

}


#ifdef __cplusplus
}
#endif
