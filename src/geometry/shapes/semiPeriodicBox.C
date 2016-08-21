#include <semiPeriodicBox.h>
#include <cmath>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
semiPeriodicBox::semiPeriodicBox() : box() {}

// Default constructor
semiPeriodicBox::semiPeriodicBox(const string& name) : box(name) {}



// Default destructor
semiPeriodicBox::~semiPeriodicBox() {}





// Member modification

// Reading properties
void semiPeriodicBox::readProperties(const std::string& dictName) {

    // Base class
    box::readProperties(dictName);

    // Read lattice size
    dictionary dict("properties/latticeProperties");
    _lsize = dict.lookUpEntry<double>("latticeSize");


    // Elements
    _nx = (uint)( ( _bbox_max.x() - _bbox_min.x() ) / _lsize ) + 1;
    _ny = (uint)( ( _bbox_max.y() - _bbox_min.y() ) / _lsize ) + 1;
    _nz = (uint)( ( _bbox_max.z() - _bbox_min.z() ) / _lsize ) + 1;

}




// Mesh construction
const vector<Vector3> semiPeriodicBox::points() const {
    

    vector<Vector3> meshPoints(_nx * _ny * _nz);
    vector<Vector3>::iterator pt = meshPoints.begin();
    
    for(uint k = 0 ; k < _nz ; k++) {
	for(uint j = 0 ; j < _ny ; j++) {
	    for(uint i = 0 ; i < _nx ; i++) {

		Vector3 v(i*_lsize + _bbox_min.x(),
			  j*_lsize + _bbox_min.y(),
			  k*_lsize + _bbox_min.z());

		*pt = v;
		pt++;
		
	    }
	}
    }


    return meshPoints;
    
}




// Neighbour construction
const vector< vector<int> > semiPeriodicBox::neighbours(const basicLBModel* lbm, const vector<Vector3>& points) const {


    // Model velocities
    vector<Vector3> velocities = lbm->latticeVel();
    
    // Create and resize neighbour matrix
    vector< vector<int> > neigh( points.size() );
    for(uint i = 0 ; i < neigh.size() ; i++)
	neigh[i].resize(lbm->Q(), -1);


    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx) + (z*Nx/Ny). The "worst" case is for a 3D box
    

    // Iterate on points
    for(uint pointId = 0 ; pointId < points.size() ; pointId++) {

    	// Iterate on velocities
    	for(uint velId = 0 ; velId < velocities.size() ; velId++) {

	    // Reverse velocity ("points" to neighbour)
    	    Vector3 vel = velocities[ lbm->reverse(velId) ];

	    // Expected index
    	    int newId = pointId + (int)vel.x() + (int)vel.y()*_nx + (int)vel.z()*_nx*_ny;

	    // Assign -1 if it is out of boundaries
	    if(  (newId >= (int)points.size())  ||  (newId < 0)  ) {
    	    	newId = -1;
	    }
	    // Assign -1 if its distance is larger than _lsize
	    else
	    {
		Vector3 diff = ( points[newId] - points[pointId] )  -  (vel * _lsize);
		if (diff.sqMag() >= 1e-10)
		    newId = -1;
		
	    }
	    
    	    neigh[pointId][velId] = newId;

    	}

    }



    // Reassign neighbours in periodic X faces
    if(_nx > 1) {

	for(uint j = 1 ; j < (_ny-1) ; j++) {
	    for(uint k = 0 ; k < _nz ; k++) {

		// Periodic indices
		uint idx0 = j*_nx + k*_nx*_ny,
		idx1 = (_nx-1) + j*_nx + k*_nx*_ny;

		// Assign missing neighbours
		for(uint velId = 0 ; velId < lbm->Q() ; velId++) {
		    
		    if(  neigh[idx0][velId] == -1  ) {
			neigh[idx0][velId] = neigh[idx1][velId];
		    }

		    if(  neigh[idx1][velId] == -1  ) {
			neigh[idx1][velId] = neigh[idx0][velId];
		    }

		}

	    }	    
	}

    }





    // Reassign neighbours in periodic X faces
    if(_nz > 1) {

	for(uint i = 1 ; i < (_nx-1) ; i++) {
	    for(uint j = 1 ; j < (_ny-1) ; j++) {

		// Periodic indices
		uint idx0 = i + j*_nx,
		    idx1 = i + j*_nx + (_nz -1)*_nx*_ny;

		// Assign missing neighbours
		for(uint velId = 0 ; velId < lbm->Q() ; velId++) {
		    
		    if(  neigh[idx0][velId] == -1  ) {
			neigh[idx0][velId] = neigh[idx1][velId];
		    }

		    if(  neigh[idx1][velId] == -1  ) {
			neigh[idx1][velId] = neigh[idx0][velId];
		    }

		}

	    }	    
	}

    }





    // Corner correction

    // Corner pairs (share some neighbours)
    vector< pair<uint, uint> > cornerPairs(4);

    // p0, p1
    cornerPairs[0] = std::make_pair(0, _nx - 1);

    // p2, p3
    cornerPairs[1] = std::make_pair(_nx * (_ny-1), _nx * _ny - 1);
    
    // p4, p5
    cornerPairs[2] = std::make_pair(_nx * _ny * (_nz-1), _nx * _ny * (_nz-1) + _nx - 1);

    // p6, p7
    cornerPairs[3] = std::make_pair(_nx * _ny * _nz - _nx, _nx * _ny * _nz - 1);


    // Move over pairs and assign missing indices
    for(uint cpair = 0 ; cpair < 4 ; cpair++) {

	// Pair indices
	uint a = get<0>(cornerPairs[cpair]);
	uint b = get<1>(cornerPairs[cpair]);
	
	for(uint velId = 0 ; velId < lbm->Q() ; velId++) {

	    if(neigh[a][velId] == -1)
		neigh[a][velId] = neigh[b][velId];

	    if(neigh[b][velId] == -1)
		neigh[b][velId] = neigh[a][velId];

	}
    
	
    }


    return neigh;

}





// Boundary map
const map<string, vector<uint>> semiPeriodicBox::boundaryMap() const {

    // Boundary map
    map<string, vector<uint>> bmap;

    // Use indices i,j,k to move over x,y,z


    if(_ny > 1) {

	// Y0
	for(uint i = 0 ; i < _nx ; i++) {
	    for(uint j = 0 ; j < 1 ; j++) {
		for(uint k = 0 ; k < _nz ; k++) {
		    bmap["semiPeriodicBox_Y0"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	}

	// Y1
	for(uint i = 0 ; i < _nx ; i++) {
	    for(uint j = _ny - 1 ; j < _ny ; j++) {
		for(uint k = 0 ; k < _nz ; k++) {
		    bmap["semiPeriodicBox_Y1"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	}    

    }



    if(_nx > 1) {

	// X0
	for(uint i = 0 ; i < 1 ; i++) {
	    for(uint j = 1 ; j < (_ny-1) ; j++) {
		for(uint k = 0 ; k < _nz ; k++) {
		    bmap["semiPeriodicBox_X0"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	}

	// X1
	for(uint i = (_nx -1) ; i < _nx ; i++) {
	    for(uint j = 1 ; j < (_ny-1) ; j++) {
		for(uint k = 0 ; k < _nz ; k++) {
		    bmap["semiPeriodicBox_X1"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	} 

    }



    if(_nz > 1) {

	// Z0
	for(uint i = 1 ; i < (_nx-1) ; i++) {
	    for(uint j = 1 ; j < (_ny-1) ; j++) {
		for(uint k = 0 ; k < 1 ; k++) {
		    bmap["semiPeriodicBox_Z0"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	}

	// Z1
	for(uint i = 1 ; i < (_nx-1) ; i++) {
	    for(uint j = 1 ; j < (_ny-1) ; j++) {
		for(uint k = (_nz-1) ; k < _nz ; k++) {
		    bmap["semiPeriodicBox_Z1"].push_back( i + j*_nx + k*_nx*_ny );
		}	    
	    }
	}

    }


    return bmap;

}




// VTK Cells
const vector< vector<uint> > semiPeriodicBox::VTKCells(const basicLBModel* lbm, const vector<Vector3>& points, const vector< vector<int> >& nbr) const {


    vector< vector<uint> > vtkCells;

    if( _nz == 1 ) {

	for(uint i = 0 ; i < (_nx-1) ; i++) {
	    for(uint j = 0 ; j < (_ny-1) ; j++) {

		vector<uint> id;

		id.push_back( i + j*_nx );
		id.push_back( i + 1 + j*_nx );
		id.push_back( i + (j+1)*_nx );
		id.push_back( i + 1 + (j+1)*_nx );
	
		vtkCells.push_back(id);
	
	    }
	}

    }




    // if(lbm->D() == 2) {


    // 	// Iterate on points
    // 	for(uint pointId = 0 ; pointId < points.size() ; pointId++) {

    // 	    vector<uint> id;
    // 	    id.push_back( pointId );

    // 	    uint pt = pointId;

    // 	    for(uint velId = 1 ; velId < 4 ; velId ++) {
    // 		int aux = nbr[pt][lbm->reverse(velId)];
    // 		if( aux != -1 ) {
    // 		    pt = aux;
    // 		    id.push_back(pt);
    // 		}
    // 	    }

    // 	    if (id.size() == 4) {
    // 		uint a = id[3];
    // 		id[3] = id[2];
    // 		id[2] = a;
    // 		vtkCells.push_back(id);
    // 	    }
	
    // 	}

	
    // }



    return vtkCells;

}
