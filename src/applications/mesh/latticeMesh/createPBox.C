#include <polyShapes.h>
#include <LBModelCreator.h>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <boost/program_options.hpp>
#include <periodicBox.h>

using namespace std;


void createPBox( boost::program_options::variables_map vm ) {

    
    // Creation of semiPeriodicBox
    periodicBox pbox("periodicBox");
    pbox.readProperties("properties/latticeProperties");

    // Point construction
    cout << "Adding points to lattice" << endl << endl;
    vector<Vector3> meshPoints = pbox.points();

    // Neighbouring calculation
    cout << "Computing neighbour indices" << endl << endl;
    LBModelCreator mcreator;
    basicLBModel* lbm = mcreator.create( vm["DQmodel"].as<string>() );
    vector< vector<int> > neigh = pbox.neighbours(lbm, meshPoints);


    // Boundary map
    cout << "Computing boundary nodes" << endl << endl;
    map<string, vector<uint>> bmap = pbox.boundaryMap();

    // VTKCells
    cout << "Creating VTK Cells" << endl << endl;
    vector< vector<uint> > vtkCells = pbox.VTKCells(lbm, meshPoints, neigh);





    // ******************************************************************** //
    //                             Writing                                  //
    // ******************************************************************** //   
    
    cout << "Writting Mesh" << endl << endl;


    // Write files
    ostringstream folder, command;
    // folder <<  "lattice/";
    folder << vm["DQmodel"].as<string>() <<  "_lattice/";
    command << "mkdir -p " << folder.str();
    int status = system( command.str().c_str() );
    if(status) {}

    ofstream outFile;

	
    // Points
    string filename = folder.str() + "points";
    outFile.open( filename.c_str() );
    if( !outFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }
    outFile << meshPoints.size() << endl;
    for(uint i = 0 ; i < meshPoints.size() ; i++) {
	outFile << meshPoints[i] << endl;
    }
    outFile.close();

    // Neighbours
    filename = folder.str() + vm["DQmodel"].as<string>() + "_neighbours";
    outFile.open( filename.c_str() );
    if( !outFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }    
    for(uint i = 0 ; i < neigh.size() ; i++) {
	for(uint j = 0 ; j < lbm->Q() ; j++) {
	    outFile << neigh[i][j] << " ";
	}
	outFile << endl;
    }
    outFile.close();    


    


    // Boundary
    filename = folder.str() + "boundary";
    outFile.open( filename.c_str() );
    if( !outFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    // Total number of boundaries
    outFile << bmap.size() << endl << endl;	

    for(auto bd : bmap) {
	outFile << bd.first << endl;
	outFile << "{" << endl;
	outFile << bd.second.size() << endl;
	for(auto bdid : bd.second) {
	    outFile << bdid << endl;
	}
	outFile << "}" << endl << endl;
    }
	
    outFile.close();





    // Write VTK cells

    filename = folder.str() + "vtkCells";
    outFile.open( filename.c_str() );
    if( !outFile.is_open() ){
	cout << "Cant't open file " << filename << endl;
	exit(1);
    }

    // Total number of cells
    outFile << vtkCells.size() << endl;
	
    for(vector< vector<uint> >::const_iterator cell = vtkCells.begin() ; cell != vtkCells.end() ; cell++) {
	outFile << cell->size() << "  ";
	for(uint cellId = 0 ; cellId < cell->size() ; cellId++) {
	    outFile << cell->at(cellId) << "  ";
	}
	outFile << endl;
    }
	
    outFile.close();    

        
}
