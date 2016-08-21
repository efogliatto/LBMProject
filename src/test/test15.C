/*
  test for Cahn-Hilliard solver.
 */


#include <cahnHilliardField.h>
#include <boost/program_options.hpp>
#include <vtkPatchWriter.h>
#include <LBModelCreator.h>

using namespace std;

int main(int argc, char** argv) {



    // ******************************************************************** //
    //                            Program options                           //
    // ******************************************************************** //

    // Define and parse the program options  
    namespace po = boost::program_options; 
    po::options_description desc("Options"); 
    desc.add_options() 
	("help,h", "Print help messages");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
 
    // --help option  
    if ( vm.count("help")  ) 
    { 
        cout << endl << "Cahn-Hilliard Lattice-Boltzmann MRT solver" << endl << endl
	     << desc << std::endl; 
        return 0; 
    } 



    

    // Start MPI communicators
    mpi::environment env;
    mpi::communicator world;
   

    // Lattice creation
    LBModelCreator creator;
    dictionary propertyDict("properties/latticeProperties");
    string modelName =  propertyDict.lookUpEntry<string>("LBModel");

    // Create time
    Time runTime;




    // Order parameter
    latticeScalarField phi( creator.create( modelName ), env, world, "phi", runTime, false );

    // Chemical potential
    latticeScalarField muPhi( creator.create( modelName ), env, world, "muPhi", runTime, false );

    // Velocity field
    latticeVectorField U( creator.create( modelName ), env, world, "U", runTime, false );

    // Lattice field
    cahnHilliardField h( creator.create( modelName ), env, world, "h", runTime, false );


    // Add fields to f list
    h.add(&phi);
    h.add(&U);
    h.addChemical(&muPhi);


    // Update initial fields using phi distribution

    // Chemical potential
    for(std::pair<cahnHilliardField::iterator, latticeScalarField::iterator> it(h.begin(), muPhi.begin()) ; it.first != h.end() ; ++it.first, ++it.second)
    	*it.second =  it.first.chemical();

    // h
    for(cahnHilliardField::iterator it = h.begin() ; it != h.end() ; ++it)
    	*it = it.equilibrium();

    
    // Synchronize ghost nodes
    h.syncGhostValues();
    phi.syncGhostValues();
    U.syncGhostValues();
    muPhi.syncGhostValues();



    // Create writer
    vtkPatchWriter writer( runTime, world.rank(), world.size(), modelName );    
    writer.add(&h, "h");
    writer.add(&U, "U");
    writer.add(&phi, "phi");
    writer.add(&muPhi, "muPhi");




    // Create collission matrices
    const Matrix Delta = h.collisionMatrix(),
	resMatrix = h.sourceMatrix();


    Time runTime2;

    // Time Loop
    while( runTime.update() ) {
	
    	if( runTime.write()  &&  (world.rank() == 0) ) {
    	    cout << endl << "Time = " << runTime.currentTime() << " s" << endl;
    	    cout << "Time step = " << runTime.countTs() << " (" << runTime.timeStep() << ")" << endl;
    	}

	
    	// Collide h
    	for(cahnHilliardField::iterator it = h.begin() ; it != h.end() ; ++it) {

	    // // Source term
	    // pdf R = resMatrix * it.source() * runTime.timeStep();

	    // // Collide
	    // *it = *it  +   Delta * ( it.equilibrium() - *it )    +    R;


	    
	    // // Collide
	    // *it = it.equilibrium();

	}

    	// // Stream h
    	// h.stream();
    
	// // Update external fields
	// h.update();
	
    	// Write fields
    	writer.write();


    	// Print info
    	if( runTime.write() ) {	    
    	    if( world.rank() == 0 ) {
    		cout << "Elapsed time = " << runTime.elapsedTime() << " s" << endl;
    	    }
    	}

	
    	// MPI barrier
    	world.barrier();
	
    }
    
    
    if( world.rank() == 0 ) {
	cout << endl << "Total time = " << runTime2.elapsedTime() << " s" << endl;
    }


    return 0;
    


}
