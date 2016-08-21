#include <iostream>
#include <latticePdfField.h>
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
    latticePdfField field(lbm, env, world, "testField", runTime);

    // Update time and write
    runTime.update();
    field.writeValues("testField", runTime.currentTime());

    
    return 0;

}
