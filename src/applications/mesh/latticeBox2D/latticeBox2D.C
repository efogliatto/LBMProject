/*

  latticeBox2D

  lattice generation in a 2D Box

*/

// #include <polyShapes.h>


// #include <algorithm>
// #include <boost/program_options.hpp>

#include <LBModelCreator.h>
#include <dictionary.h>
#include <sstream>
#include <fstream>
#include <map>
#include <periodicX.h>
#include <periodicY.h>

using namespace std;




int main(int argc, char** argv) {

   
    cout << endl;
    cout << "CREATION OF LATTICE MESH" << endl << endl;


    // Basic lattice properties
    dictionary latticeDict("properties/latticeProperties");

    // Lattice size
    const uint nx = (uint)latticeDict.lookUpEntry<double>("Nx");
    const uint ny = (uint)latticeDict.lookUpEntry<double>("Ny");

    // Lattice model
    LBModelCreator mcreator;
    basicLBModel* lbm = mcreator.create(    latticeDict.lookUpEntry<string>("LBModel")  );

    // Boundary type
    string bdType = latticeDict.lookUpEntry<string>("boundaryType");
    



    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    
    cout << "Adding points to lattice" << endl << endl;

    
    // Points container
    vector<Vector3> meshPoints(nx * ny);

    
    // Move over indices

    uint id(0);   

    for(uint j = 0 ; j < ny ; j++) {
	
    	for(uint i = 0 ; i < nx ; i++) {

    	    Vector3 v(i, j, 0);
			    
    	    meshPoints[id] = v;
    	    id++;
		
    	}
    }




    
    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //
    
    cout << "Computing neighbour indices" << endl << endl;

    vector<Vector3> velocities = lbm->latticeVel();
    
    
    // Create and resize neighbour matrix
    vector< vector<int> > neigh(meshPoints.size());
    
    for(uint i = 0 ; i < neigh.size() ; i++) {
	
    	neigh[i].resize(lbm->Q(), -1);
	
    }

    

    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx).
    

    // Iterate on points
    for(int pointId = 0 ; pointId < (int)meshPoints.size() ; pointId++) {


    	// Iterate on velocities
    	for(int velId = 0 ; velId < (int)velocities.size() ; velId++) {

    	    // Discrete velocity
    	    Vector3 vel = velocities[ lbm->reverse(velId) ];
	    
    	    // Predicted index
    	    int newId = pointId + (int)vel.x() + (int)vel.y()*nx;

	    
    	    Vector3 diff = meshPoints[newId] - meshPoints[pointId] - vel;

	    
    	    if(  diff.sqMag()  <= 1.0e-10  ) {
		
    		neigh[pointId][velId] = newId;
			
    	    }
	    

    	}

    }
	






    

	    
    
    // ******************************************************************** //
    //                             Boundary                                 //
    // ******************************************************************** //

    cout << "Computing boundary nodes" << endl << endl;
  

    // Boundary map
    map<string, vector<uint>> bmap = periodicY(neigh, nx, ny, lbm->Q());


    // 	    // Iterate on points
    // 	    for(int pointId = 0 ; pointId < (int)meshPoints.size() ; pointId++) {

    // 	    	// Check if point is on boundary
    // 	    	string sname = figura.pointOverBoundary( meshPoints[pointId], 1.4142*lsize );
    // 	    	if(!sname.empty()) {
    // 	    	    bmap[sname].push_back(pointId);
    // 	    	}
	
    // 	    }



	    

    


    // 	    // ******************************************************************** //
    // 	    //                             VTK Cells                                //
    // 	    // ******************************************************************** //

    // 	    cout << "Creating VTK Cells" << endl << endl;
    
    // 	    vector< vector<uint> > vtkCells;

    // 	    if(lbm->D() == 2) {


    // 	    	// Iterate on points
    // 	    	for(uint pointId = 0 ; pointId < meshPoints.size() ; pointId++) {
    // 	    	    // for(uint pointId = 0 ; pointId < 1 ; pointId++) {

    // 	    	    vector<uint> id;
    // 	    	    id.push_back( pointId );

    // 	    	    uint pt = pointId;

    // 	    	    for(uint velId = 1 ; velId < 4 ; velId ++) {
    // 	    		int aux = neigh[pt][lbm->reverse(velId)];
    // 	    		if( aux != -1 ) {
    // 	    		    pt = aux;
    // 	    		    id.push_back(pt);
    // 	    		}
    // 	    	    }

    // 	    	    if (id.size() == 4) {
    // 	    		uint a = id[3];
    // 	    		id[3] = id[2];
    // 	    		id[2] = a;
    // 	    		vtkCells.push_back(id);
    // 	    	    }
	
    // 	    	}

	
    // 	    }







    


	    


    // ******************************************************************** //
    //                             Writing                                  //
    // ******************************************************************** //   
    
    cout << "Writting Mesh" << endl << endl;


    // Write files
    ostringstream folder, command;
    // folder <<  "lattice/";
    folder << lbm->name() <<  "_lattice/";
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
    filename = folder.str() + lbm->name() + "_neighbours";
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





    // 	    // Write VTK cells

    // 	    filename = folder.str() + "vtkCells";
    // 	    outFile.open( filename.c_str() );
    // 	    if( !outFile.is_open() ){
    // 	    	cout << "Cant't open file " << filename << endl;
    // 	    	exit(1);
    // 	    }

    // 	    // Total number of cells
    // 	    outFile << vtkCells.size() << endl;
	
    // 	    for(vector< vector<uint> >::const_iterator cell = vtkCells.begin() ; cell != vtkCells.end() ; cell++) {
    // 	    	outFile << cell->size() << "  ";
    // 	    	for(uint cellId = 0 ; cellId < cell->size() ; cellId++) {
    // 	    	    outFile << cell->at(cellId) << "  ";
    // 	    	}
    // 	    	outFile << endl;
    // 	    }
	
    // 	    outFile.close();    



	
	    
	    
    // 	}
	



    // }
    // 

    return 0;

}
