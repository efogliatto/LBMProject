// Write field for c-written solvers

#include <writeVectorField.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif


void writeVectorField(const char* fname, const double** field, const struct solverInfo* info) {

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
	outFile << field[i][0] << std::endl;
	outFile << field[i][1] << std::endl;
	outFile << field[i][2] << std::endl;
    }
    
    // Close file
    outFile.close();

}


#ifdef __cplusplus
}
#endif
