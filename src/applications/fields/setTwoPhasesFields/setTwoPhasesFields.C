/*
  Two phase solver, recovering Cahn-Hilliard.
 */


#include <cahnHilliardField.h>
#include <liangField.h>
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
	("help,h", "Print help messages")
	("initialFields", po::bool_switch()->default_value(false), "Create initial fields only");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
 
    // --help option  
    if ( vm.count("help")  ) 
    { 
        cout << endl << "Set fields for twoPhasesMRT" << endl << endl
	     << desc << std::endl; 
        return 0; 
    } 



    

    // Start MPI communicator
    mpi::environment env;
    mpi::communicator world;


    if(world.rank() == 0) {

	cout << endl << "SETTING FIELDS FOR TWOPHASESMRT" << endl;
	
    }
    

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


    // Add fields to h list
    h.add(&phi);
    h.add(&U);
    h.addChemical(&muPhi);


    

    // Density
    latticeScalarField rho( creator.create( modelName ), env, world, "rho", runTime, false );

    // Pressure
    latticeScalarField p( creator.create( modelName ), env, world, "p", runTime, false );

    // Lattice field
    liangField g( creator.create( modelName ), env, world, "g", runTime, false );

    // Add fields to g list
    g.add(&phi);
    g.add(&U);
    g.add(&rho);
    g.add(&p);
    g.add(&muPhi);

    
    
    // Synchronize ghost nodes
    h.syncGhostValues();
    g.syncGhostValues();


    // Create writer
    vtkPatchWriter writer( runTime, world.rank(), world.size(), modelName );    
    writer.add(&h, "h");
    writer.add(&U, "U");
    writer.add(&phi, "phi");
    writer.add(&muPhi, "muPhi");
    writer.add(&p, "p");
    writer.add(&rho, "rho");
    writer.add(&g, "g");
    

    if( vm["initialFields"].as<bool>() == true ) {


	// Chemical potential
	for(std::pair<cahnHilliardField::iterator, latticeScalarField::iterator> it(h.begin(), muPhi.begin()) ; it.first != h.end() ; ++it.first, ++it.second)
	    *it.second =  it.first.chemical();
    
	// h equilibrium
	for(cahnHilliardField::iterator it = h.begin() ; it != h.end() ; ++it)
	    *it = it.equilibrium();


	// rho
	for(std::pair<liangField::iterator, latticeScalarField::iterator> it(g.begin(), rho.begin()) ; it.first != g.end() ; ++it.first, ++it.second)
	    *it.second =  it.first.density();    

	// p
	{
	    latticeVectorField::iterator uiter = U.begin();
	    for(std::pair<liangField::iterator, latticeScalarField::iterator> it(g.begin(), p.begin()) ; it.first != g.end() ; ++it.first, ++it.second) {
		*it.second =  it.first.zerothMoment( *uiter );
		++uiter;
	    }

	}
    
	// g
	for(liangField::iterator it = g.begin() ; it != g.end() ; ++it)
	    *it = it.equilibrium();


	// Synchronize ghost nodes
	h.syncGhostValues();
	g.syncGhostValues();
	p.syncGhostValues();
	rho.syncGhostValues();
	phi.syncGhostValues();
	muPhi.syncGhostValues();
	U.syncGhostValues();
	
	writer.write();


	// // Write in binary format
	// h.writeBinary();
	// U.writeBinary();
	// phi.writeBinary();
	// muPhi.writeBinary();
	// p.writeBinary();
	// rho.writeBinary();
	// g.writeBinary();
	

	
    }

    // Read from current time and write in VTK format
    else {

	while( runTime.update() ) {

	    if( runTime.write() ) {

		phi.readAllValues();
		muPhi.readAllValues();
		rho.readAllValues();
		U.readAllValues();
		h.readAllValues();
		p.readAllValues();
		g.readAllValues();

		// Synchronize ghost nodes
		h.syncGhostValues();
		g.syncGhostValues();
		p.syncGhostValues();
		rho.syncGhostValues();
		phi.syncGhostValues();
		muPhi.syncGhostValues();
		U.syncGhostValues();
		
		writer.write();

	    }
	    
	}
	
    }



    if(world.rank() == 0) {
	cout << setprecision(3);
	cout << endl << "    Finished in " << runTime.elapsedTime() << " seconds" << endl << endl;
	
    }    
    
    return 0;
}
