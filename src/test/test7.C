#include <iostream>
#include <latticeField.h>
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

    // Create MPI patch and read structure during construction
    latticeField<int> field(lbm, env, world, "testField", runTime);


    // Write values after sync
    if( world.rank() == 0 ) {

    	cout << endl;
	
    	for(lbPatch_iterator<int> it = field.begin() ; it != field.end() ; ++it) {
	    
    	    for(vector< pair<uint, int*> >::iterator neighIt = it.neighBegin() ; neighIt != it.neighEnd() ; ++neighIt) {
		
    	    	cout << "(" << neighIt->first << ")" << *(neighIt->second) << "   " ;
		
    	    }
	    
    	    cout << endl;
	    
    	}
	
    	cout << endl;
	
    }



    
    return 0;

}
