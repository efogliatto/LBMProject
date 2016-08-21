#include <iostream>
#include <latticePdfField.h>
#include <latticeVectorField.h>
#include <latticeScalarField.h>
#include <vtkPatchWriter.h>
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

    // Create writer
    vtkPatchWriter writer( runTime, world.rank(), world.size(), "D2Q9" );    

    // Create latticePdfField
    latticePdfField pdfField(lbm, env, world, "g", runTime, false);

    // Create latticeVectorField
    latticeVectorField vectorField(lbm, env, world, "U", runTime, false);

    // Create latticePdfField
    latticeScalarField scalarField(lbm, env, world, "phi", runTime, false);


    // Link fields to writer
    writer.add(&pdfField, "g");
    writer.add(&vectorField, "U");
    writer.add(&scalarField, "phi");

    
    // Update time and write
    runTime.update();
    writer.write();

    
    return 0;

}
