#include <iostream>
#include <mpiPatch.h>
#include <Time.h>
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

    if( world.rank() ) {	
    
	mpiPatch<int> parche(lbm,10000000, env, world);

	Time runTime;
    
	for(int i = 0 ; i < 500 ; i++) {
	    for(basicPatch_iterator<int> it = parche.begin() ; it != parche.end() ; ++it) {
		it.setValue(i);
	    }
	}

	cout << "Nuevo:   " << runTime.elapsedTime() << endl;

    }



    // Create MPI patch and read structure during construction
    mpiPatch<int> ppatch(lbm, env, world);

    // Read values from some fiels
    ppatch.readValues("testField","");

    // Synchronize skeletons
    ppatch.syncSkeletons();

    // Synchronize ghost values
    ppatch.syncGhostValues();

    // Write values after sync
    if( world.rank() == 1 ) {

    	cout << endl;
	
    	for(lbPatch_iterator<int> it = ppatch.begin() ; it != ppatch.end() ; ++it) {
	    
    	    for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
		
    	    	cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
		
    	    }
	    
    	    cout << endl;
	    
    	}
	
    	cout << endl;
	
    }



    
    return 0;

}
