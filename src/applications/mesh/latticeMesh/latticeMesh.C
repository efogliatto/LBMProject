/*
  latticeMesh
 */

#include <polyShapes.h>
#include <LBModelCreator.h>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <boost/program_options.hpp>

#include <createSPBox.h>
#include <createPBox.h>

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
	("semiPeriodicBox", po::bool_switch()->default_value(false), "Construct a box, periodic in y-direction")
	("periodicBox", po::bool_switch()->default_value(false), "Construct a periodic box")	
	("noBoundary", po::bool_switch()->default_value(false), "Mesh without bounday. All neighbours set for bounceBack, except those for periodic directions");	

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
    cout << "CREATION OF LATTICE MESH" << endl << endl;

    

    // Special case: SEMI-PERIODIC BOX
    if( vm["semiPeriodicBox"].as<bool>() == true ) {

	createSPBox( vm );
	   
    }





    else {


	if( vm["periodicBox"].as<bool>() == true ) {

	    createPBox( vm );

	}

	
	// Basic shapes
	else {




	    cout << "Creating polyShape from properties" << endl << endl;
    
	    polyShapes figura("properties/latticeProperties");


    

	    // ******************************************************************** //
	    //                         Points inside geometry                       //
	    // ******************************************************************** //

	    cout << "Adding points to lattice" << endl << endl;
    
	    // Read lattice size
	    dictionary dict("properties/latticeProperties");
	    double lsize = dict.lookUpEntry<double>("latticeSize");

	
	    // Create mesh
	    tuple<Vector3, Vector3> bbox = figura.boundingBox();
	    Vector3 bboxMin = get<0>(bbox);

	    uint nx = (uint)( (get<1>(bbox).x() - get<0>(bbox).x()) / lsize ) + 1;
	    uint ny = (uint)( (get<1>(bbox).y() - get<0>(bbox).y()) / lsize ) + 1;
	    uint nz = (uint)( (get<1>(bbox).z() - get<0>(bbox).z()) / lsize ) + 1;

    
	    vector<Vector3> meshPoints(nx * ny * nz);

	    {
		uint id = 0;
    
		for(uint k = 0 ; k < nz ; k++) {
		    for(uint j = 0 ; j < ny ; j++) {
			for(uint i = 0 ; i < nx ; i++) {

			    Vector3 v(i*lsize + bboxMin.x(),
				      j*lsize + bboxMin.y(),
				      k*lsize + bboxMin.z());
		    
			    if (figura.locatePoint(v)) {
				meshPoints[id] = v;
				id++;
			    }
		
			}
		    }
		}


		// Remove last elements from _points
		if( meshPoints.size() != id ) {
		    int excess =  meshPoints.size() - id;
		    meshPoints.erase( meshPoints.end() - excess,  meshPoints.end() );
		}
	    }


    


	    // ******************************************************************** //
	    //                             Neighbours                               //
	    // ******************************************************************** //
    
	    cout << "Computing neighbour indices" << endl << endl;

	    LBModelCreator mcreator;
	    basicLBModel* lbm = mcreator.create( vm["DQmodel"].as<string>() );

	    vector<Vector3> velocities = lbm->latticeVel();
    
    
	    // Create and resize neighbour matrix
	    vector< vector<int> > neigh(meshPoints.size());
	    for(uint i = 0 ; i < neigh.size() ; i++) {
		neigh[i].resize(lbm->Q(), -1);
	    }


	    // Check for neighbouring
	    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
	    // p with index pointId is at most at pointId + x + (y*Nx) + (z*Nx/Ny). The "worst" case is for a 3D box
    

	    // Iterate on points
	    for(int pointId = 0 ; pointId < (int)meshPoints.size() ; pointId++) {

		// Iterate on velocities
		for(int velId = 0 ; velId < (int)velocities.size() ; velId++) {

		    Vector3 vel = velocities[ lbm->reverse(velId) ];

		    int newId = pointId + (int)vel.x() + (int)vel.y()*nx + (int)vel.z()*nx*ny;

		    // Iterate in backward direction (minimices the number of searches)
		    if (newId >= pointId) {

			if(newId >= (int)meshPoints.size()) { newId = meshPoints.size()-1; }

			bool find = false;
			while( (newId >= pointId)  &&  (find == false) ) {

			    Vector3 diff = ( meshPoints[newId] - meshPoints[pointId] )  -  (vel * lsize);

			    if(  diff.sqMag()  <= 1.0e-10  ) {
				find = true;
				neigh[pointId][velId] = newId;
			    }
			    newId--;
			}

		    }

	    
	    
		    // Iterate in forward direction
		    else {
			if(newId < 0) { newId = 0; }

			bool find = false;
			while( (newId <= pointId)  &&  (find == false) ) {		   

			    Vector3 diff = ( meshPoints[newId] - meshPoints[pointId] )  -  (vel * lsize);

			    if(  diff.sqMag()  <= 1.0e-10  ) {
				find = true;
				neigh[pointId][velId] = newId;
			    }
		    
			    newId++;

			}

		    }



		}

	    }
	


    
	    // ******************************************************************** //
	    //                             Boundary                                 //
	    // ******************************************************************** //

	    cout << "Computing boundary nodes" << endl << endl;

	    // Boundary map
	    map<string, vector<uint>> bmap;


	    // Iterate on points
	    for(int pointId = 0 ; pointId < (int)meshPoints.size() ; pointId++) {

		// Check if point is on boundary
		string sname = figura.pointOverBoundary( meshPoints[pointId], 1.4142*lsize );
		if(!sname.empty()) {
		    bmap[sname].push_back(pointId);
		}
	
	    }




    


	    // ******************************************************************** //
	    //                             VTK Cells                                //
	    // ******************************************************************** //

	    cout << "Creating VTK Cells" << endl << endl;
    
	    vector< vector<uint> > vtkCells;

	    if(lbm->D() == 2) {


		// Iterate on points
		for(uint pointId = 0 ; pointId < meshPoints.size() ; pointId++) {
		    // for(uint pointId = 0 ; pointId < 1 ; pointId++) {

		    vector<uint> id;
		    id.push_back( pointId );

		    uint pt = pointId;

		    for(uint velId = 1 ; velId < 4 ; velId ++) {
			int aux = neigh[pt][lbm->reverse(velId)];
			if( aux != -1 ) {
			    pt = aux;
			    id.push_back(pt);
			}
		    }

		    if (id.size() == 4) {
			uint a = id[3];
			id[3] = id[2];
			id[2] = a;
			vtkCells.push_back(id);
		    }
	
		}

	
	    }





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
	



    }


    return 0;

}
