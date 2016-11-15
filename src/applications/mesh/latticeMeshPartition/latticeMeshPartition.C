/*
  latticeMeshPartition
 */

#include <polyShapes.h>
#include <LBModelCreator.h>
#include <map>
#include <algorithm>
#include <boost/program_options.hpp>
#include <IOPatch.h>

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
	("DQmodel,d", po::value<string>()->required(), "LBM model type (D dimensions with Q velocities)")
	("processors,n", po::value<int>()->required(), "number of processors")
	("version,v", po::value<string>()->default_value("new"), "partition version");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
 
    // --help option  
    if ( vm.count("help")  ) 
    { 
        cout << endl << "Construction of lattice mesh" << endl << endl
	     << desc << std::endl; 
        return 0; 
    } 

    

    cout << endl;
    cout << "MESH PARTITIONING" << endl << endl;
    
    polyShapes figura("properties/latticeProperties");


    
    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    cout << "Reading Mesh points" << endl << endl;
    
    // string filename = "lattice/points";
    string filename = vm["DQmodel"].as<string>() + "_lattice/points";
    ifstream inFile;    
    inFile.open( filename.c_str() );
    if( !inFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    // Number of points
    uint npoints;
    inFile >> npoints;

    // Read Mesh points
    vector<Vector3> meshPoints( npoints );
    for(uint i = 0 ; i < npoints ; i++) {
	inFile >> meshPoints[i];
    }

    inFile.close();


 


    


    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    cout << "Reading Neighbour indices" << endl << endl;    

    LBModelCreator mcreator;
    basicLBModel* lbm = mcreator.create( vm["DQmodel"].as<string>() );

    vector<Vector3> velocities = lbm->latticeVel();
    
    
    // Create and resize neighbour matrix
    vector< vector<int> > neigh( meshPoints.size() );
    for(uint i = 0 ; i < neigh.size() ; i++) {
	neigh[i].resize(lbm->Q(), -1);
    }

    // Read indices
    filename = vm["DQmodel"].as<string>() + "_lattice/" + vm["DQmodel"].as<string>() + "_neighbours";
    inFile.open( filename.c_str() );
    if( !inFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    for(uint i = 0 ; i < neigh.size() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    inFile >> neigh[i][j];
	}
    }

    inFile.close();

    


    


    // ******************************************************************** //
    //                             VTK Cells                                //
    // ******************************************************************** //

    cout << "Reading VTK Cells" << endl << endl;

    // filename = "lattice/vtkCells";
    filename = vm["DQmodel"].as<string>() + "_lattice/vtkCells";
    inFile.open( filename.c_str() );
    if( !inFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    // Number of cells
    uint ncells;
    inFile >> ncells;

    vector< vector<uint> > vtkCells( ncells );


    for(uint i = 0 ; i < ncells ; i++) {

	uint npc;
	inFile >> npc;

	vtkCells[i].resize( npc );
	
	for(uint j = 0 ; j < npc ; j++) {
	    inFile >> vtkCells[i][j];
	}
	
    }

    inFile.close();

	


    


    // ******************************************************************** //
    //                        Reading boundary nodes                        //
    // ******************************************************************** //

    cout << "Reading boundary nodes" << endl << endl;

    filename = vm["DQmodel"].as<string>() + "_lattice/boundary";
    inFile.open( filename.c_str() );
    if( !inFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    // Boundary map
    map<string, vector<uint>> globalBmap;
    
    // Read total number of boundaries
    int nBound;
    inFile >> nBound;

    // Read boundaries
    for(int i = 0 ; i < nBound ; i++) {

	// Read boundary name
	std::string name,
	    aux;
	inFile >> name;

	// Read opening brace
	inFile >> aux;

	// Read number of indices per boundary
	int nIdx;
	inFile >> nIdx;

	globalBmap[name].resize( nIdx );

	for(int j = 0 ; j < nIdx ; j++) {

	    // Read indices
	    inFile >> globalBmap[name][j];
	    
	}

	// Read closing brace
	inFile >> aux;	
	
    }

    inFile.close();





    
    
    
    // ******************************************************************** //
    //                             Processors                               //
    // ******************************************************************** //


    cout << "Decomposing domain" << endl;


    // Split on processors
    const uint np = vm["processors"].as<int>();
    vector<uint> procBegin(np),
    	procEnd(np);

    for(uint i = 0 ; i < np ; i++ ) {
    	if(i != 0) {
    	    procBegin[i] = procEnd[i-1] + 1;
    	    procEnd[i] = procBegin[i] + (int)(meshPoints.size()/np) - 1;
    	}
    	else {
    	    procBegin[i] = 0;
    	    procEnd[0] = (int)(meshPoints.size()/np) - 1;
    	}
    }
    procEnd[np - 1] = meshPoints.size() - 1;

    
    // Ownership vector
    vector<uint> owner;
    owner.resize( meshPoints.size() );

    for(uint pid = 0 ; pid < np ; pid++) {
    	for(uint i = procBegin[pid] ; i <= procEnd[pid] ; i++) {
    	    owner[i] = pid;
    	}
    }

    
    // Create set of IOPatchs, according to number of processors
    vector< IOPatch<Vector3> > patches;

    for(uint pid = 0 ; pid < np ; pid++)
    	patches.push_back( IOPatch<Vector3>(lbm) );

    // Set patch indices
    for(uint pid = 0 ; pid < np ; pid++)
    	patches[pid].setId(pid);

    // Assign neighbours
    for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++)
    	it->setGlobalNeighbours( neigh, owner );

    // Assign values
    for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++)
    	it->setValues( meshPoints );        


    // Set send maps
    for(uint i = 0 ; i < patches.size() ; i++) {

    	for(uint j = 0 ; j < patches.size() ; j++) {

    	    if( i != j ) {

    		patches[i].setSendMap( patches[j].id(), patches[j].ghostRecvGId( patches[i].id() ) );
		
    	    }
	    
    	}
	
    }    


    // Assign boundary elements
    for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++)
	it->setGlobalBdMap( globalBmap );
    
    

    // Write patch information
    for(uint pid = 0 ; pid < patches.size() ; pid++) {

    	cout << "    processor" << pid << endl; 

    	ostringstream folderName;
    	folderName << "processor" << pid << "/" << vm["DQmodel"].as<string>() << "_lattice";

    	// Neighbours
    	patches[pid].writeNeighboursIds(  "neighbours", folderName.str() );

    	// Global Ids, local nodes
    	patches[pid].writeGlobalIdLocal(  "globalIds", folderName.str() );

    	// Global indices, ghost nodes
    	patches[pid].writeGlobalIdGhost(  "globalGhostsIds", folderName.str() );	

    	// Recv map indices
    	patches[pid].writeRecvMapsIds(  "recvMapIds", folderName.str() );

    	// Send map indices
    	patches[pid].writeSendMapsIds(  "sendMapIds", folderName.str() );

    	// Local and ghost values
    	patches[pid].writeAllValues(  "points", folderName.str() );

    	// VTK Cells
    	patches[pid].writeVTKCells(  "vtkCells", folderName.str(), vtkCells );

	// Boundary elements
	patches[pid].writeBoundariesIds(  "boundary", folderName.str() );
	
    }

    cout << endl << "Finished domain decomposition" << endl << endl;
    
    
    return 0;

}
