#include <iostream>
#include <latticeScalarField.h>
#include <LBModelCreator.h>

using namespace std;

int main() {

    // MPI environments
    mpi::environment env;
    mpi::communicator world;

    // Only 2 processes
    if( (world.size()>2) && (world.rank()==0) ) {
	cout << "More than two processes" << endl;
	exit(1);
    }    

    LBModelCreator mc;
    
    basicLBModel* lbm = mc.create("D2Q9");
   
    Time runTime;

    // Create latticeScalarField
    latticeScalarField field(lbm, env, world, "testField", runTime);


    // Print differential operators
    if( world.rank() == 0 ) {

    	cout << "Laplacian" << endl;
	
    	for(latticeScalarField::iterator it = field.begin() ; it != field.end() ; ++it) {
	    
	    cout << it.laplacian() << endl;
	    
    	}
	
    	cout << endl;


    	cout << "Gradient" << endl;
	
    	for(latticeScalarField::iterator it = field.begin() ; it != field.end() ; ++it) {
	    
	    cout << it.gradient() << endl;
	    
    	}
	
    	cout << endl;	
	
    }



    
    return 0;

}
