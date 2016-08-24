/*
  Two phase solver, recovering Cahn-Hilliard.
 */


#include <cahnHilliardField.h>
// #include <LiangField.h>
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
        cout << endl << "Two Phase, Lattice-Boltzmann MRT solver. Uses Cahn-Hilliard equation" << endl << endl
	     << desc << std::endl; 
        return 0; 
    } 



    

    // Start MPI communicator
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


    // Add fields to h list
    h.add(&phi);
    h.add(&U);
    h.addChemical(&muPhi);


    // h
    for(cahnHilliardField::iterator it = h.begin() ; it != h.end() ; ++it)
    	*it = it.equilibrium();

    

    // Density
    latticeScalarField rho( creator.create( modelName ), env, world, "rho", runTime, false );

    // Pressure
    latticeScalarField p( creator.create( modelName ), env, world, "p", runTime, false );

    // // Lattice field
    // liangField g( creator.create( modelName ), env, world, "g", runTime, false );

    // // Add fields to g list
    // g.add(&phi);
    // g.add(&U);
    // g.add(&rho);
    // g.add(&p);
    // g.addChemical(&muPhi);


    // // g
    // for(liangField::iterator it = g.begin() ; it != g.end() ; ++it)
    // 	*it = it.equilibrium();    

    // // Synchronize ghost nodes
    // h.syncGhostValues();
    // g.syncGhostValues();



    // Create writer
    vtkPatchWriter writer( runTime, world.rank(), world.size(), modelName );    
    writer.add(&h, "h");
    writer.add(&U, "U");
    writer.add(&phi, "phi");
    writer.add(&muPhi, "muPhi");
    writer.add(&p, "p");
    writer.add(&rho, "rho");
    // writer.add(&g, "g");


    writer.write();


    
    
    return 0;
}
